(include "rm-simulator.scm")

; a: Our updated fibonacci machine
(define fib-machine
  (make-machine
    '(n val continue)
    (list
      (list '< <) (list '- -) (list '+ +))
    '((assign continue (label fib-done))
      fib-loop
        (test (op <) (reg n) (const 2))
        (branch (label immediate-answer))
        (save continue)
        (assign continue (label afterfib-n-1))
        (save n)
        (assign n (op -) (reg n) (const 1))
        (goto (label fib-loop))
      afterfib-n-1
        (restore n)
        (assign n (op -) (reg n) (const 2))
        (assign continue (label afterfib-n-2))
        (save val)
        (goto (label fib-loop))
      afterfib-n-2
        (assign n (reg val))
        (restore val)
        (restore continue)
        (assign val (op +) (reg val) (reg n))
        (goto (reg continue))
      immediate-answer
        (assign val (reg n))
        (goto (reg continue))
      fib-done)))

(set-register-contents! fib-machine 'n 10)
(start fib-machine)
(display (get-register-contents fib-machine 'val))
(newline)

; b: changes to the restore instruction, so that the value being restored is the same as the last continue
(define (make-save inst machine stack pc)
  (let ((reg-name (stack-inst-reg-name inst)))
    (let ((reg (get-register machine reg-name)))
      (lambda ()
        (push stack (cons reg-name (get-contents reg)))
        (advance-pc pc)))))

(define (make-restore inst machine stack pc)
  (let ((reg-name (stack-inst-reg-name inst)))
    (let ((reg (get-register machine reg-name)))
      (lambda ()
        (let ((stored-reg (pop stack)))
          (let ((stored-reg-name (car stored-reg)))
            (if (eq? reg-name stored-reg-name)
              (begin
                (set-contents! reg (cdr stored-reg))
                (advance-pc pc))
              (error "Wrong register restored -- MAKE-RESTORE"))))))))

(define fib-machine-2
  (make-machine
    '(n val continue)
    (list
      (list '< <) (list '- -) (list '+ +))
    '((assign continue (label fib-done))
      fib-loop
        (test (op <) (reg n) (const 2))
        (branch (label immediate-answer))
        (save continue)
        (assign continue (label afterfib-n-1))
        (save n)
        (assign n (op -) (reg n) (const 1))
        (goto (label fib-loop))
      afterfib-n-1
        (restore n)
        (assign n (op -) (reg n) (const 2))
        (assign continue (label afterfib-n-2))
        (save val)
        (goto (label fib-loop))
      afterfib-n-2
        (assign n (reg val))
        (restore val)
        (restore continue)
        (assign val (op +) (reg val) (reg n))
        (goto (reg continue))
      immediate-answer
        (assign val (reg n))
        (goto (reg continue))
      fib-done)))

(set-register-contents! fib-machine-2 'n 15)
(start fib-machine-2)
(display (get-register-contents fib-machine-2 'val))
(newline)

; c: changes to have a separate stack for each register
; the machine does not need an overall stack
(define (make-new-machine)
  (let ((pc (make-register 'pc))
        (flag (make-register 'flag))
        (the-instruction-sequence '()))
    (let ((the-ops
            (list (list 'initialize-stack
                        (lambda ()
                          (for-each (lambda (reg)
                                      (reg 'initialize-stack))
                                    register-table)))))
          (register-table
            (list (list 'pc pc) (list 'flag flag))))
      (define (allocate-register name)
        (if (assoc name register-table)
          (error "Multiple defined register: " name)
          (set! register-table
            (cons (list name (make-register name))
                  register-table)))
        'register-allocated)
      (define (lookup-register name)
        (let ((val (assoc name register-table)))
          (if val
            (cadr val)
            (error "Unknown register: " name))))
      (define (execute)
        (let ((insts (get-contents pc)))
          (if (null? insts)
            'done
            (begin
              ((instruction-execution-proc (car insts)))
              (execute)))))
      (define (dispatch message)
        (cond ((eq? message 'start)
               (set-contents! pc the-instruction-sequence)
               (execute))
              ((eq? message 'install-instruction-sequence)
               (lambda (seq) (set! the-instruction-sequence seq)))
              ((eq? message 'allocate-register) allocate-register)
              ((eq? message 'get-register) lookup-register)
              ((eq? message 'install-operations)
               (lambda (ops) (set! the-ops (append the-ops ops))))
              ((eq? message 'operations) the-ops)
              (else
                (error "Unknown request -- MACHINE" message))))
      dispatch)))

; each register has it's own stack
(define (make-register name)
  (let ((contents '*unassigned*)
        (stack (make-stack)))
    (define (dispatch message)
      (cond ((eq? message 'get) contents)
            ((eq? message 'set)
             (lambda (value) (set! contents value)))
            ((eq? message 'initialize-stack)
             (stack 'initialize))
            ((eq? message 'stack) stack)
            (else
              (error "Unknown request -- REGISTER" message))))
    dispatch))

; updates here to not pass the stack of the machine
(define (update-insts! insts labels machine)
  (let ((pc (get-register machine 'pc))
        (flag (get-register machine 'flag))
        (ops (machine 'operations)))
    (for-each
      (lambda (inst)
        (set-instruction-execution-proc!
          inst
          (make-execution-procedure
            (instruction-text inst) labels machine
            pc flag ops)))
      insts)))

; updates here to not pass the stack of the machine
(define (make-execution-procedure inst labels machine pc flag ops)
  (cond ((eq? (car inst) 'assign)
         (make-assign inst machine labels ops pc))
        ((eq? (car inst) 'test)
         (make-test inst machine labels ops flag pc))
        ((eq? (car inst) 'branch)
         (make-branch inst machine labels flag pc))
        ((eq? (car inst) 'goto)
         (make-goto inst machine labels pc))
        ((eq? (car inst) 'save)
         (make-save inst machine pc))
        ((eq? (car inst) 'restore)
         (make-restore inst machine pc))
        ((eq? (car inst) 'perform)
         (make-perform inst machine labels ops pc))
        (else
          (error "Unknown instruction type -- ASSEMBLE" inst))))

; use the stack of the register on the save instruction
(define (make-save inst machine pc)
  (let ((reg (get-register machine
                           (stack-inst-reg-name inst))))
    (let ((reg-stack (reg 'stack)))
      (lambda ()
        (push reg-stack (get-contents reg))
        (advance-pc pc)))))

; use the stack of the register on the restore instruction
(define (make-restore inst machine pc)
  (let ((reg (get-register machine
                           (stack-inst-reg-name inst))))
    (let ((reg-stack (reg 'stack)))
      (lambda ()
        (set-contents! reg (pop reg-stack))
        (advance-pc pc)))))

(define fib-machine-3
  (make-machine
    '(n val continue)
    (list
      (list '< <) (list '- -) (list '+ +))
    '((assign continue (label fib-done))
      fib-loop
        (test (op <) (reg n) (const 2))
        (branch (label immediate-answer))
        (save continue)
        (assign continue (label afterfib-n-1))
        (save n)
        (assign n (op -) (reg n) (const 1))
        (goto (label fib-loop))
      afterfib-n-1
        (restore n)
        (assign n (op -) (reg n) (const 2))
        (assign continue (label afterfib-n-2))
        (save val)
        (goto (label fib-loop))
      afterfib-n-2
        (assign n (reg val))
        (restore val)
        (restore continue)
        (assign val (op +) (reg val) (reg n))
        (goto (reg continue))
      immediate-answer
        (assign val (reg n))
        (goto (reg continue))
      fib-done)))

(set-register-contents! fib-machine-3 'n 20)
(start fib-machine-3)
(display (get-register-contents fib-machine-3 'val))
(newline)
