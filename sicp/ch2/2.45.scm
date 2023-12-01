#lang sicp
(#%require sicp-pict)
; this program can only be run in dr racket

(define (split op1 op2)
  (define (splitter painter n)
    (if (= n 0)
      painter
      (let ((smaller (splitter painter (- n 1))))
        (op1 painter (op2 smaller smaller)))))
  splitter)

(define right-split (split beside below))
(define up-split (split below beside))

(paint (up-split einstein 4))
(paint (right-split einstein 4))
