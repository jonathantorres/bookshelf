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

(define (ramanujan)
  (define (cube n)
    (* n n n))
  (define (weight p)
    (+ (cube (car p)) (cube (cadr p))))
  (define (iter s)
    (let ((p1 (stream-car s))
          (p2 (stream-car (stream-cdr s))))
      (if (= (weight p1) (weight p2))
        (cons-stream (weight p1)
                     (iter (stream-cdr s)))
        (iter (stream-cdr s)))))
  (let ((nums (weighted-pairs integers integers weight)))
    (iter nums)))

(define ones (cons-stream 1 ones))
(define integers (cons-stream 1 (add-streams ones integers)))

(display-stream (ramanujan))
