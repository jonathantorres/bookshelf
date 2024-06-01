(include "rm-simulator.scm")

(define append-machine
  (make-machine
    '(val tmp x y continue)
    (list
      (list 'null? null?) (list 'cons cons)
      (list 'cdr cdr) (list 'car car))
    '((assign continue (label append-done))
      append-loop
        (test (op null?) (reg x))
        (branch (label assign-case))
        (save continue)
        (assign continue (label after-append))
        (save x)
        (assign x (op cdr) (reg x))
        (goto (label append-loop))
      after-append
        (restore x)
        (restore continue)
        (assign tmp (op car) (reg x))
        (assign val (op cons) (reg tmp) (reg val))
        (goto (reg continue))
      assign-case
        (assign val (reg y))
        (goto (reg continue))
    append-done)))

(set-register-contents! append-machine 'x (list 1 2 3))
(set-register-contents! append-machine 'y (list 4 5 6))
(start append-machine)
(display (get-register-contents append-machine 'val))
(newline)

(define append!-machine
  (make-machine
    '(val last x y)
    (list
      (list 'null? null?) (list 'cdr cdr)
      (list 'set-cdr! set-cdr!))
    '((assign last (reg x))
      last-pair-loop
        (assign val (op cdr) (reg last))
        (test (op null?) (reg val))
        (branch (label last-pair-done))
        (assign last (op cdr) (reg last))
        (goto (label last-pair-loop))
      last-pair-done
        (assign val (op set-cdr!) (reg last) (reg y))
        (assign val (reg x))
      done)))

(set-register-contents! append!-machine 'x (list 1 2 3))
(set-register-contents! append!-machine 'y (list 4 5 6))
(start append!-machine)
(display (get-register-contents append!-machine 'val))
(newline)
