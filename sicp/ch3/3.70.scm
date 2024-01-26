(include "streams.scm")

(define (merge-weighted s1 s2 w)
  (cond ((stream-null? s1) s2)
        ((stream-null? s2) s1)
        (else
         (let ((s1car (stream-car s1))
               (s2car (stream-car s2)))
           (let ((s1w (w s1car))
                 (s2w (w s2car)))
             (if (< s1w s2w)
               (cons-stream s1car (merge-weighted (stream-cdr s1) s2 w))
               (cons-stream s2car (merge-weighted s1 (stream-cdr s2) w))))))))

(define (weighted-pairs s t w)
  (cons-stream
    (list (stream-car s) (stream-car t))
    (merge-weighted
      (stream-map (lambda (x) (list (stream-car s) x)) (stream-cdr t))
      (weighted-pairs (stream-cdr s) (stream-cdr t) w)
      w)))

; a: the stream of all pairs of positive integers (i,j) with i<=j ordered according to the sum i+j
(define (pos-pairs-a)
  (weighted-pairs
    integers
    integers
    (lambda (x) (+ (car x) (cadr x)))))

; b: the stream of all pairs of positive integers (i,j) with i<=j where neither i nor j
;    is divisible by 2, 3, or 5, and the pairs are ordered according to the sum 2i+3j+5ij
(define (pos-pairs-b)
  (define (divisible n)
    (not
      (or (= (remainder n 2) 0)
          (= (remainder n 3) 0)
          (= (remainder n 5) 0))))
  (define (weight p)
    (let ((i (car p))
          (j (cadr p)))
      (+
        (* 2 i)
        (* 3 j)
        (* 5 i j))))

  (let ((nums (stream-filter divisible integers)))
    (weighted-pairs
      nums
      nums
      weight)))

(define ones (cons-stream 1 ones))
(define integers (cons-stream 1 (add-streams ones integers)))

(display-stream (pos-pairs-a))
(display-stream (pos-pairs-b))
