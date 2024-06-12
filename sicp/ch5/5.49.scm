(include "ec-evaluator.scm")
(include "compiler.scm")

; same procedure as 5.48
(define (compile-and-run exp)
  (assemble (statements (compile exp 'val 'return))
            rce-machine))

; add new operations
(define rce-operations (append ec-operations (list
                                               (list 'compile-and-run compile-and-run))))

(define rce-machine
  (make-machine
    '(exp env val proc argl continue unev)
    rce-operations
    '(read-eval-print-loop
        (perform (op initialize-stack))
        (perform (op prompt-for-input) (const ";;; RCE-Eval input:"))
        (assign exp (op read))
        (assign env (op get-global-environment))
        (assign continue (label print-result))
        (assign val (op compile-and-run) (reg exp))
        (goto (reg val))
      print-result
        (perform (op announce-output) (const ";;; RCE value:"))
        (perform (op user-print) (reg val))
        (goto (label read-eval-print-loop))
      done)))

(set-register-contents! rce-machine 'env the-global-environment)
(start rce-machine)

; for this machine, you can type any declarations or use the factorial procedure to test:
; (define (factorial n) (if (= n 1) 1 (* (factorial (- n 1)) n)))

; and then enter:
; (factorial 5)
; it should return 120 
