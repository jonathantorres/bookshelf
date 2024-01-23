(include "streams.scm")

(define (integrate-series s)
  (define (iter ss i)
    (cons-stream (/ (stream-car ss) i)
                 (iter (stream-cdr ss) (+ i 1))))
  (iter s 1))

(define (mul-series s1 s2)
  (cons-stream
    (* (stream-car s1) (stream-car s2))
    (add-streams (mul-series (stream-cdr s1) s2)
                 (scale-stream (stream-cdr s2) (stream-car s1)))))

(define (invert-unit-series s)
  (cons-stream 1
               (stream-map (lambda (x) (- x))
                           (mul-series (stream-cdr s) (invert-unit-series s)))))

(define (div-series n d)
  (if (= (stream-car d) 0)
    (error "cannot divide by a power series with constant term set to 0")
    (mul-series n (invert-unit-series d))))

(define sine-series
  (cons-stream 0 (integrate-series
                   (cons-stream 1
                                (integrate-series
                                  (stream-map (lambda (x) (- x)) sine-series))))))
(define cosine-series
  (cons-stream 1 (integrate-series
                   (cons-stream 0
                                (stream-map (lambda (x) (- x))
                                            (integrate-series cosine-series))))))

(define tangent-series (div-series sine-series cosine-series))

(display-stream tangent-series)
