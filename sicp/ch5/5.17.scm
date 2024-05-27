(include "rm-simulator.scm")

; extending instruction tracing on the machine
(define (make-new-machine)
  (let ((pc (make-register 'pc))
        (flag (make-register 'flag))
        (stack (make-stack))
        (labels '())
        (the-instruction-sequence '())
        (instruction-count 0)
        (tracing #f))
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
      (define (display-label instruction)
        (for-each (lambda (label-list)
                    (let ((label-name (car label-list))
                          (label-insts (if (pair? (cdr label-list))
                                         (list-ref (cdr label-list) 0)
                                         '())))
                      (if (and
                            (pair? label-insts)
                            (eq? instruction label-insts))
                        (begin
                          (display label-name)
                          (newline)))))
                  labels))
      (define (execute)
        (let ((insts (get-contents pc)))
          (if (null? insts)
            'done
            (let ((trace-on tracing)
                  (instruction (car insts)))
              (if trace-on
                (begin
                  (display-label instruction)
                  (display "  ")
                  (display (instruction-text instruction))
                  (newline)))
              ((instruction-execution-proc instruction))
              (set! instruction-count (+ instruction-count 1))
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
              ((eq? message 'set-labels)
               (lambda (ls) (set! labels ls)))
              ((eq? message 'instruction-count)
               (let ((count instruction-count))
                 (set! instruction-count 0)
                 count))
              ((eq? message 'trace-on) (set! tracing #t))
              ((eq? message 'trace-off) (set! tracing #f))
              (else
                (error "Unknown request -- MACHINE" message))))
      dispatch)))

; updates on "assemble" so that the labels are stored
(define (assemble controller-text machine)
  (let ((result (extract-labels controller-text)))
    (let ((insts (car result))
          (labels (cdr result)))
      (update-insts! insts labels machine)
      ((machine 'set-labels) labels)
      insts)))

(define (trace-on machine)
  (machine 'trace-on))

(define (trace-off machine)
  (machine 'trace-off))

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

(set-register-contents! fib-machine 'n 3)
(trace-on fib-machine)
(start fib-machine)
(display (get-register-contents fib-machine 'val))
(newline)
