(include "amb.scm")

(define prog
  '((define (require p)
      (if (not p) (amb)))
    (define (an-integer-starting-from n)
      (amb n (an-integer-starting-from (+ n 1))))
    (define (an-integer-between low high)
      (if (> low high)
        (require (<= low high))
        (amb low (an-integer-between (+ low 1) high))))
    (define (pythagorean-triples n)
      (let ((i (an-integer-starting-from n)))
        (let ((j (an-integer-between n i)))
          (let ((k (an-integer-between j i)))
            (require (= (+ (* j j) (* k k)) (* i i)))
            (list j k i)))))
    (begin
      (display (pythagorean-triples 1))
      (newline))))

(define (run)
  (define env (setup-environment))
  (for-each (lambda (p)
              (ambeval p env
                       (lambda (value fail) (cons value (fail)))
                       (lambda () 'ok)))
            prog))

(run)
