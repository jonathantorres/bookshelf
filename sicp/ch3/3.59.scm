(include "streams.scm")

; a: the integrate-series procedure
(define (integrate-series s)
  (define (iter ss i)
    (cons-stream (/ (stream-car ss) i)
                 (iter (stream-cdr ss) (+ i 1))))
  (iter s 1))

; b: cosine and sine series
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

(display-stream cosine-series)
(display-stream sine-series)
