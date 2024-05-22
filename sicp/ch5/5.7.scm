(include "rm-simulator.scm")

; recursive exponentiation machine
(define recursive-expt-machine
  (make-machine
    '(n b val continue)
    (list
      (list '= =) (list '* *) (list '- -))
    '((assign continue (label expt-done))
       expt-loop
         (test (op =) (reg n) (const 0))
         (branch (label expt-base))
         (save continue)
         (assign n (op -) (reg n) (const 1))
         (assign continue (label after-expt))
         (goto (label expt-loop))
       after-expt
         (restore continue)
         (assign val (op *) (reg b) (reg val))
         (goto (reg continue))
       expt-base
         (assign val (const 1))
         (goto (reg continue))
       expt-done)))

(set-register-contents! recursive-expt-machine 'b 2)
(set-register-contents! recursive-expt-machine 'n 8)
(start recursive-expt-machine)
(display (get-register-contents recursive-expt-machine 'val))
(newline)

; iterative exponentiation machine
(define iterative-expt-machine
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

(set-register-contents! iterative-expt-machine 'b 2)
(set-register-contents! iterative-expt-machine 'n 8)
(start iterative-expt-machine)
(display (get-register-contents iterative-expt-machine 'product))
(newline)
