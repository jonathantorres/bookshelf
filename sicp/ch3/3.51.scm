(include "streams.scm")

(define (show x)
  (display x)
  (newline)
  x)

(define x (stream-map show (stream-enumerate-interval 0 10)))

(stream-ref x 5) ; outputs: 5
(stream-ref x 7) ; outputs: 7

