(define (sum term a next b)
  (if (> a b)
    0
    (+ (term a) (sum term (next a) next b))))

(define (integral f a b dx)
  (define (add-dx x) (+ x dx))
  (* (sum f (+ a (/ dx 2.0)) add-dx b)
     dx))

(define (simpson f a b n)
  (define h (/ (- b a) n))
  (define (next a)
    (+ a 1))
  (define (term k)
    (define c
      (cond ((= k 0) 1.0)
            ((= k n) 1.0)
            ((even? k) 2.0)
            (else 4.0)))
    (* c (f (+ a (* k h)))))
  (* (/ h 3) (sum term a next n)))

(define (cube x)
  (* x x x))

(display (integral cube 0 1 0.01)) (newline)
(display (integral cube 0 1 0.001)) (newline)
(display (simpson cube 0 1 100)) (newline)
(display (simpson cube 0 1 1000)) (newline)
