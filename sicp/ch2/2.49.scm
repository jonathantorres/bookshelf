#lang sicp
(#%require sicp-pict)
; this program can only be run in dr racket

; painter that draws the outline of the frame
(define outline-segments (list
                           (make-segment (make-vect 0 0) (make-vect 0 1))
                           (make-segment (make-vect 0 1) (make-vect 1 1))
                           (make-segment (make-vect 1 1) (make-vect 1 0))
                           (make-segment (make-vect 1 0) (make-vect 0 0))))
(define outline (segments->painter outline-segments))

; painter that draws an "X"
(define x-segments (list
                     (make-segment (make-vect 0 1) (make-vect 1 0))
                     (make-segment (make-vect 0 0) (make-vect 1 1))))
(define x (segments->painter x-segments))

; painter that draws a diamond
(define diamond-segments (list
                           (make-segment (make-vect 0 0.5) (make-vect 0.5 1))
                           (make-segment (make-vect 0.5 1) (make-vect 1 0.5))
                           (make-segment (make-vect 1 0.5) (make-vect 0.5 0))
                           (make-segment (make-vect 0.5 0) (make-vect 0 0.5))))
(define diamond (segments->painter diamond-segments))

; the wave painter
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
                        (make-segment (make-vect 0.5 0.3) (make-vect 0.4 0))))
(define wave (segments->painter wave-segments))


; draw the painters
(paint outline)
(paint x)
(paint diamond)
(paint wave)
