(include "amb.scm")

(define prog
  '((define (require p)
      (if (not p) (amb)))
    (define (an-integer-between low high)
      (if (> low high)
        (require (<= low high))
        (amb low (an-integer-between (+ low 1) high))))
    (define (a-pythagorean-triple-between low high)
      (let ((i (an-integer-between low high)))
        (let ((j (an-integer-between i high)))
          (let ((k (an-integer-between j high)))
            (require (= (+ (* i i) (* j j)) (* k k)))
            (list i j k)))))
    (begin
      (display (a-pythagorean-triple-between 10 100))
      (newline))))

(define (run)
  (define env (setup-environment))
  (for-each (lambda (p)
              (ambeval p env
                       (lambda (value fail) (cons value (fail)))
                       (lambda () 'ok)))
            prog))

(run)
