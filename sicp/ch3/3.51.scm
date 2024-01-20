(include "streams.scm")

(define (show x)
  (display x)
  (newline)
  x)

(define x (stream-map show (stream-enumerate-interval 0 10)))

; guile outputs:
; 0
; 1
; 2
; 3
; 4
; 5
; 6
; 7
; 8
; 9
; 10

(stream-ref x 5) ; returns 5
(stream-ref x 7) ; returns 7

