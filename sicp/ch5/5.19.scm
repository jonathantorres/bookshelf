(include "rm-simulator.scm")

; changes on make-new-machine to support breakpoints
(define (make-new-machine)
  (let ((pc (make-register 'pc))
        (flag (make-register 'flag))
        (stack (make-stack))
        (the-instruction-sequence '())
        (labels '())
        (breakpoints '()))
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
      (define (set-breakpoint label n)
        (if (null? breakpoints)
          (set! breakpoints (list (list label n)))
          (set! breakpoints (append breakpoints (list (list label n))))))
      (define (remove-breakpoint label n)
        (let ((bp (delete (list label n) breakpoints)))
          (set! breakpoints bp)))
      (define (lookup-breakpoint inst)
        (let ((found #f))
          (for-each (lambda (bp)
                      (let ((label (car bp))
                            (n (cadr bp)))
                        (let ((label-insts (assoc label labels)))
                          (if label-insts
                            (let ((cur-inst (list-ref label-insts (- n 1))))
                              (if (eq? cur-inst inst)
                                (set! found (cons label cur-inst))))))))
                    breakpoints)
          found))
      (define (execute)
        (let ((insts (get-contents pc)))
          (if (null? insts)
            'done
            (let ((inst (car insts)))
              (let ((bp (lookup-breakpoint inst)))
                (if bp
                  (begin
                    (display "breakpoint: ")
                    (display (car bp))
                    (display ": ")
                    (display (instruction-text inst))
                    (newline)
                    'done)
                  (begin
                    ((instruction-execution-proc (car insts)))
                    (execute))))))))
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
              ((eq? message 'continue) (execute))
              ((eq? message 'set-breakpoint)
               (lambda (label n) (set-breakpoint label n)))
              ((eq? message 'remove-breakpoint)
               (lambda (label n) (remove-breakpoint label n)))
              ((eq? message 'remove-breakpoints) (set! breakpoints '()))
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

(define (set-breakpoint machine label n)
  ((machine 'set-breakpoint) label n))

(define (cancel-breakpoint machine label n)
  ((machine 'remove-breakpoint) label n))

(define (cancel-all-breakpoints machine)
  (machine 'remove-breakpoints))

(define (proceed-machine machine)
  (machine 'continue))

; gcd machine for testing
(define gcd-machine
  (make-machine
    '(a b t)
    (list
      (list '= =) (list 'rem remainder))
    '(test-b
       (test (op =) (reg b) (const 0))
       (branch (label gcd-done))
       (assign t (op rem) (reg a) (reg b))
       (assign a (reg b))
       (assign b (reg t))
       (goto (label test-b))
    gcd-done)))

(set-register-contents! gcd-machine 'a 206)
(set-register-contents! gcd-machine 'b 40)
(set-breakpoint gcd-machine 'test-b 4)
(start gcd-machine)
(display (get-register-contents gcd-machine 'a))
(newline)

(cancel-all-breakpoints gcd-machine)
(proceed-machine gcd-machine)
(display (get-register-contents gcd-machine 'a))
(newline)

