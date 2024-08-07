(include "rm-simulator.scm")

; changes to enable register tracing
(define (make-register name)
  (let ((contents '*unassigned*)
        (tracing #f))
    (define (dispatch message)
      (cond ((eq? message 'get) contents)
            ((eq? message 'set)
             (lambda (value)
               (begin
                 (if (eq? tracing #t)
                   (begin
                     (display "register(")
                     (display name)
                     (display ") old=")
                     (display contents)
                     (display " new=")
                     (display value)
                     (newline)))
                 (set! contents value))))
            ((eq? message 'trace-on)
             (set! tracing #t))
            ((eq? message 'trace-off)
             (set! tracing #f))
            (else
              (error "Unknown request -- REGISTER" message))))
    dispatch))

; enable tracing on registers
(define (make-new-machine)
  (let ((pc (make-register 'pc))
        (flag (make-register 'flag))
        (stack (make-stack))
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
      (define (trace-registers registers)
        (for-each (lambda (register-name)
                    (let ((register (lookup-register register-name)))
                      (register 'trace-on)))
                  registers))
      (define (untrace-registers)
        (for-each (lambda (reg-entry)
                    (let ((register (cadr reg-entry)))
                      (register 'trace-off)))
                  register-table))
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
              ((eq? message 'register-trace-on)
               (lambda (registers) (trace-registers registers)))
              ((eq? message 'register-trace-off) (untrace-registers))
              (else
                (error "Unknown request -- MACHINE" message))))
      dispatch)))

(define (register-trace-on machine registers)
  ((machine 'register-trace-on) registers))

(define (register-trace-off machine)
  (machine 'register-trace-off))

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

(register-trace-on fib-machine '(n val))
(set-register-contents! fib-machine 'n 5)
(start fib-machine)
(display (get-register-contents fib-machine 'val))
(newline)
