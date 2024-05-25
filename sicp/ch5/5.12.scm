(include "rm-simulator.scm")

; making a new machine
(define (make-new-machine)
  (let ((pc (make-register 'pc))
        (flag (make-register 'flag))
        (stack (make-stack))
        (execd-instructions '())
        (entry-points '())
        (regs-saved-or-restored '())
        (reg-sources '())
        (the-instruction-sequence '()))
    (let ((the-ops
            (list (list 'initialize-stack
                        (lambda () (stack 'initialize)))))
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
      (define (store-in-list l val)
        (define (val-in-list l val)
          (if (or (null? l) (not (memq val l)))
            #f
            #t))
        (if (not (val-in-list l val))
          (append l (list val))
          l))
      (define (display-data-paths)
        (begin
          (display "Machine Data Paths: ")
          (newline)
          (display "instructions: ")
          (display execd-instructions)
          (newline)
          (display "entry points: ")
          (display entry-points)
          (newline)
          (display "saved or restored: ")
          (display regs-saved-or-restored)
          (newline)
          (display "register sources: ")
          (display reg-sources)
          (newline)))
      (define (store-execd-instruction inst-name)
        (set! execd-instructions (store-in-list execd-instructions inst-name)))
      (define (store-entry-point reg-name)
        (set! entry-points (store-in-list entry-points reg-name)))
      (define (store-saved-or-restored-register reg-name)
        (set! regs-saved-or-restored (store-in-list regs-saved-or-restored reg-name)))
      (define (store-register-source reg-name source)
        (let ((def (assoc reg-name reg-sources)))
          (if def
            (set-cdr! def (cons source (cdr def)))
            (set! reg-sources
              (cons (list reg-name (list source)) reg-sources)))))
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
              ((eq? message 'stack) stack)
              ((eq? message 'operations) the-ops)
              ((eq? message 'display-data-paths) (display-data-paths))
              ((eq? message 'store-execd-instruction)
               (lambda (inst-name) (store-execd-instruction inst-name)))
              ((eq? message 'store-entry-point)
               (lambda (reg-name) (store-entry-point reg-name)))
              ((eq? message 'store-saved-or-restored-register)
               (lambda (reg-name) (store-saved-or-restored-register reg-name)))
              ((eq? message 'store-register-source)
               (lambda (reg-name source) (store-register-source reg-name source)))
              (else
                (error "Unknown request -- MACHINE" message))))
      dispatch)))

; changes to store the list of all instructions
(define (make-execution-procedure inst labels machine pc flag stack ops)
  (let ((inst-name (car inst)))
    ((machine 'store-execd-instruction) inst-name)
    (cond ((eq? inst-name 'assign)
           (make-assign inst machine labels ops pc))
          ((eq? inst-name 'test)
           (make-test inst machine labels ops flag pc))
          ((eq? inst-name 'branch)
           (make-branch inst machine labels flag pc))
          ((eq? inst-name 'goto)
           (make-goto inst machine labels pc))
          ((eq? inst-name 'save)
           (make-save inst machine stack pc))
          ((eq? inst-name 'restore)
           (make-restore inst machine stack pc))
          ((eq? inst-name 'perform)
           (make-perform inst machine labels ops pc))
          (else
            (error "Unknown instruction type -- ASSEMBLE" inst)))))

; changes to store entry points
(define (make-goto inst machine labels pc)
  (let ((dest (goto-dest inst)))
    (cond ((label-exp? dest)
           (let ((insts
                   (lookup-label labels
                                 (label-exp-label dest))))
             (lambda () (set-contents! pc insts))))
          ((register-exp? dest)
           (let ((reg-name (register-exp-reg dest)))
             (let ((reg (get-register machine reg-name)))
               ((machine 'store-entry-point) reg-name)
               (lambda ()
                 (set-contents! pc (get-contents reg))))))
          (else
            (error "Bad GOTO instruction -- ASSEMBLE" inst)))))

; changes to store registers that are saved or restored
(define (make-save inst machine stack pc)
  (let ((reg-name (stack-inst-reg-name inst)))
    (let ((reg (get-register machine reg-name)))
      ((machine 'store-saved-or-restored-register) reg-name)
      (lambda ()
        (push stack (get-contents reg))
        (advance-pc pc)))))

(define (make-restore inst machine stack pc)
  (let ((reg-name (stack-inst-reg-name inst)))
    (let ((reg (get-register machine reg-name)))
      ((machine 'store-saved-or-restored-register) reg-name)
      (lambda ()
        (set-contents! reg (pop stack))
        (advance-pc pc)))))

; changes to store register sources
(define (make-assign inst machine labels operations pc)
  (let ((reg-name (assign-reg-name inst)))
    (let ((target (get-register machine reg-name))
          (value-exp (assign-value-exp inst)))
      ((machine 'store-register-source) reg-name value-exp)
      (let ((value-proc
              (if (operation-exp? value-exp)
                (make-operation-exp
                  value-exp machine labels operations)
                (make-primitive-exp
                  (car value-exp) machine labels))))
        (lambda ()
          (set-contents! target (value-proc))
          (advance-pc pc))))))

(define (display-data-paths machine)
  (machine 'display-data-paths))

; fibonacci machine for testing
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
(display-data-paths fib-machine)
(display (get-register-contents fib-machine 'val))
(newline)
