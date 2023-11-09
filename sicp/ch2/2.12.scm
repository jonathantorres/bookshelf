(define (make-center-percent c p)
  (let ((w (* c (/ p 100))))
    (make-center-width c w)))

(define (percent i)
  (let ((c (center i))
        (w (width i)))
    (* (/ w c) 100)))

(define (make-center-width c w)
  (make-interval (- c w) (+ c w)))

(define (center i)
  (/ (+ (lower-bound i) (upper-bound i)) 2))

(define (width i)
  (/ (- (upper-bound i) (lower-bound i)) 2))

(define (make-interval a b)
  (cons a b))

(define (lower-bound x)
  (car x))

(define (upper-bound x)
  (cdr x))

(define i (make-center-percent 100 5))

(display (center i)) (newline)
(display (percent i)) (newline)
