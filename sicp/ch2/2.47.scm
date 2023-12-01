; constructor and selectors for the first representation
(define (make-frame origin edge1 edge2)
  (list origin edge1 edge2))

(define (origin-frame f)
  (car f))

(define (edge1-frame f)
  (cadr f))

(define (edge2-frame f)
  (caddr f))

; constructor and selectors for the second representation
(define (make-frame origin edge1 edge2)
  (cons origin (cons edge1 edge2)))

(define (origin-frame f)
  (car f))

(define (edge1-frame f)
  (cadr f))

(define (edge2-frame f)
  (cddr f))


; test for the selectors
(define frame (make-frame 1 2 3))
(display (origin-frame frame)) (newline) ; 1
(display (edge1-frame frame)) (newline)  ; 2
(display (edge2-frame frame)) (newline)  ; 3
