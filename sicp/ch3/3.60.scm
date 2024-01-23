(include "streams.scm")

(define (integrate-series s)
  (define (iter ss i)
    (cons-stream (/ (stream-car ss) i)
                 (iter (stream-cdr ss) (+ i 1))))
  (iter s 1))

(define cosine-series
  (cons-stream 1 (integrate-series
                   (cons-stream 0
                                (stream-map (lambda (x) (- x))
                                            (integrate-series cosine-series))))))

(define sine-series
  (cons-stream 0 (integrate-series
                   (cons-stream 1
                                (integrate-series
                                  (stream-map (lambda (x) (- x)) sine-series))))))

(define (mul-series s1 s2)
  (cons-stream
    (* (stream-car s1) (stream-car s2))
    (add-streams (mul-series (stream-cdr s1) s2)
                 (scale-stream (stream-cdr s2) (stream-car s1)))))

(display-stream (mul-series cosine-series sine-series))
