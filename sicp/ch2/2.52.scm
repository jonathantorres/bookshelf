#lang sicp
(#%require sicp-pict)
; this program can only be run in dr racket

(define (right-split painter n)
  (if (= n 0)
    painter
    (let ((smaller (right-split painter (- n 1))))
      (beside painter (below smaller smaller)))))

(define (up-split painter n)
  (if (= n 0)
    painter
    (let ((up (up-split painter (- n 1))))
      (below painter (beside up up)))))

(define (square-of-four tl tr bl br)
  (lambda (painter)
    (let ((top (beside (tl painter) (tr painter)))
          (bottom (beside (bl painter) (br painter))))
      (below bottom top))))

(define (square-limit painter n)
  (let ((combine4 (square-of-four flip-horiz identity
                                  rotate180 flip-vert)))
    (combine4 (corner-split painter n))))

(define (square-limit-out painter n)
  (let ((combine4 (square-of-four flip-vert rotate180
                                  identity flip-horiz)))
    (combine4 (corner-split painter n))))

(define (corner-split painter n)
  (if (= n 0)
    painter
    (let ((up (up-split painter (- n 1)))
          (right (right-split painter (- n 1))))
      (let ((top-left (beside up up))
            (bottom-right (below right right))
            (corner (corner-split painter (- n 1))))
        (beside (below painter top-left)
                (below bottom-right corner))))))

(define (corner-split-single painter n)
  (if (= n 0)
    painter
    (let ((top-left (up-split painter (- n 1)))
          (bottom-right (right-split painter (- n 1))))
      (let ((corner (corner-split painter (- n 1))))
        (beside (below painter top-left)
                (below bottom-right corner))))))

; the wave painter with a smile :)
(define wave-segments (list
                        (make-segment (make-vect 0.25 0) (make-vect 0.35 0.5))
                        (make-segment (make-vect 0.35 0.5) (make-vect 0.3 0.6))
                        (make-segment (make-vect 0.3 0.6) (make-vect 0.15 0.4))
                        (make-segment (make-vect 0.15 0.4) (make-vect 0 0.65))
                        (make-segment (make-vect 0 0.85) (make-vect 0.15 0.6))
                        (make-segment (make-vect 0.15 0.6) (make-vect 0.3 0.65))
                        (make-segment (make-vect 0.3 0.65) (make-vect 0.4 0.65))
                        (make-segment (make-vect 0.4 0.65) (make-vect 0.35 0.85))
                        (make-segment (make-vect 0.35 0.85) (make-vect 0.4 1))
                        (make-segment (make-vect 0.6 1) (make-vect 0.65 0.85))
                        (make-segment (make-vect 0.65 0.85) (make-vect 0.6 0.65))
                        (make-segment (make-vect 0.6 0.65) (make-vect 0.75 0.65))
                        (make-segment (make-vect 0.75 0.65) (make-vect 1 0.35))
                        (make-segment (make-vect 1 0.15) (make-vect 0.6 0.45))
                        (make-segment (make-vect 0.6 0.45) (make-vect 0.75 0))
                        (make-segment (make-vect 0.6 0) (make-vect 0.5 0.3))
                        (make-segment (make-vect 0.5 0.3) (make-vect 0.4 0))
                        (make-segment (make-vect 0.44 0.7) (make-vect 0.51 0.7))))
(define wave (segments->painter wave-segments))

; a: wave painter with a smile
(paint (square-limit wave 4))

; b: using a different pattern for corner-split
(paint (corner-split-single einstein 4))

; c: square-limit with the corners in a different pattern
(paint (square-limit-out einstein 4))
