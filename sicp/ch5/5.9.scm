(include "rm-simulator.scm")

; updates on make-operation-exp to signal an error if a label is used as an operator
(define (make-operation-exp exp machine labels operations)
  (let ((op (lookup-prim (operation-exp-op exp) operations))
        (aprocs
          (map (lambda (e)
                 (if (or (register-exp? e) (constant-exp? e))
                   (make-primitive-exp e machine labels)
                   (error "Bad operator -- ASSEMBLE" (car e))))
               (operation-exp-operands exp))))
    (lambda ()
      (apply op (map (lambda (p) (p)) aprocs)))))

; test machine with a correct use of "op"
(define ok-machine
  (make-machine
    '(n b product counter)
    (list
      (list '= =) (list '* *) (list '- -))
    '((assign counter (reg n))
      (assign product (const 1))
       expt-loop
         (test (op =) (reg counter) (const 0))
         (branch (label expt-done))
         (assign counter (op -) (reg counter) (const 1))
         (assign product (op *) (reg b) (reg product))
         (goto (label expt-loop))
       expt-done)))

(set-register-contents! ok-machine 'b 2)
(set-register-contents! ok-machine 'n 8)
(start ok-machine)
(display (get-register-contents ok-machine 'product))
(newline)

; bad machine with incorrect use of "op" (uncomment to test)
; (define bad-machine
;   (make-machine
;     '(n b product counter)
;     (list
;       (list '= =) (list '* *) (list '- -))
;     '((assign counter (reg n))
;       (assign product (const 1))
;        expt-loop
;          (test (op =) (reg counter) (const 0))
;          (branch (label expt-done))
;          (assign counter (op -) (reg counter) (const 1))
;          (assign product (op *) (reg b) (label expt-done))
;          (goto (label expt-loop))
;        expt-done)))

; (set-register-contents! bad-machine 'b 2)
; (set-register-contents! bad-machine 'n 8)
; (start bad-machine)
; (display (get-register-contents bad-machine 'product))
; (newline)
