#lang sicp
(#%require sicp-pict)
; this program can only be run in dr racket

(define (up-split painter n)
  (if (= n 0)
    painter
    (let ((up (up-split painter (- n 1))))
      (below painter (beside up up)))))

(paint (up-split einstein 4))
