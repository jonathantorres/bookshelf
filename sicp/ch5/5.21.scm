(include "rm-simulator.scm")

(define clr-machine
  (make-machine
    '(val pair-test n continue tree)
    (list
      (list 'null? null?) (list 'not not) (list 'pair? pair?)
      (list 'car car) (list 'cdr cdr) (list '+ +))
    '((assign continue (label count-done))
      count-loop
        (test (op null?) (reg tree))
        (branch (label null-case))
        (assign pair-test (op pair?) (reg tree))
        (test (op not) (reg pair-test))
        (branch (label not-pair-case))
        (save continue)
        (assign continue (label after-car-count))
        (save tree)
        (assign tree (op car) (reg tree))
        (goto (label count-loop))
      after-car-count
        (restore tree)
        (assign tree (op cdr) (reg tree))
        (assign continue (label after-cdr-count))
        (save val)
        (goto (label count-loop))
      after-cdr-count
        (assign n (reg val))
        (restore val)
        (restore continue)
        (assign val (op +) (reg n) (reg val))
        (goto (reg continue))
      not-pair-case
        (assign val (const 1))
        (goto (reg continue))
      null-case
        (assign val (const 0))
        (goto (reg continue))
    count-done)))

(set-register-contents! clr-machine 'tree (list (list 1 2) 3 4 (list 5 6) 7))
(start clr-machine)
(display (get-register-contents clr-machine 'val)) ; 7 leaves
(newline)

(define clc-machine
  (make-machine
    '(val pair-test n continue tree)
    (list
      (list 'null? null?) (list 'not not) (list 'pair? pair?)
      (list 'car car) (list 'cdr cdr) (list '+ +))
    '((assign continue (label count-done))
      (assign n (const 0))
      count-loop
        (test (op null?) (reg tree))
        (branch (label null-case))
        (assign pair-test (op pair?) (reg tree))
        (test (op not) (reg pair-test))
        (branch (label not-pair-case))
        (save continue)
        (save tree)
        (assign tree (op car) (reg tree))
        (assign continue (label after-count))
        (goto (label count-loop))
      after-count
        (restore tree)
        (restore continue)
        (assign n (reg val))
        (assign tree (op cdr) (reg tree))
        (goto (label count-loop))
      not-pair-case
        (assign val (op +) (reg n) (const 1))
        (goto (reg continue))
      null-case
        (assign val (reg n))
        (goto (reg continue))
    count-done)))
        
(set-register-contents! clc-machine 'tree (list (list 1 2) 3 4 (list 5 6)))
(start clc-machine)
(display (get-register-contents clc-machine 'val)) ; 6 leaves
(newline)
