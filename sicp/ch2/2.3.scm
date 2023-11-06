(define (make-segment x y)
  (cons x y))

(define (start-segment s)
  (car s))

(define (end-segment s)
  (cdr s))

(define (make-point x y)
  (cons x y))

(define (x-point p)
  (car p))

(define (y-point p)
  (cdr p))

(define (midpoint-segment s)
  (define (avg x y)
    (/ (+ x y) 2))
  (let ((start (start-segment s))
        (end (end-segment s)))
    (make-point
      (avg (x-point start) (x-point end))
      (avg (y-point start) (y-point end)))))

; calculate the length of a segment
(define (length-segment s)
  (let ((start (start-segment s))
        (end (end-segment s)))
    (sqrt
      (+ (square (- (x-point end) (x-point start)))
         (square (- (y-point end) (y-point start)))))))

(define (print-point p)
  (newline)
  (display "(")
  (display (x-point p))
  (display ",")
  (display (y-point p))
  (display ")"))

(define nil 0)
(define (isnull? x)
  (if (= x nil) #t #f))

; make rectangle using pairs
; one pair for the top/bottom
; another pair for the left/right
(define (make-rect top bot left right)
  (cons
    (cons top bot)
    (cons left right)))

(define (rect-top r) (car (car r)))
(define (rect-bottom r) (cdr (car r)))
(define (rect-left r) (car (cdr r)))
(define (rect-right r) (cdr (cdr r)))
(define (rect-height r)
  (length-segment (rect-left r)))
(define (rect-width r)
  (length-segment (rect-top r)))

; make rectangle using a list
; the top is the first element
; the bottom is the second element
; the left is the third element
; the right is the fourth element
(define (make-rect top bot left right)
  (cons top
    (cons bot
      (cons left
        (cons right nil)))))

(define (rect-top r) (car r))
(define (rect-bottom r) (car (cdr r)))
(define (rect-left r) (car (cdr (cdr r))))
(define (rect-right r) (car (cdr (cdr (cdr r)))))
(define (rect-height r)
  (length-segment (rect-left r)))
(define (rect-width r)
  (length-segment (rect-top r)))

(define (square x) (* x x))

; calculate the perimeter of a rectangle (any representation)
(define (rect-perimeter r)
  (+
    (length-segment (rect-top r))
    (length-segment (rect-bottom r))
    (length-segment (rect-left r))
    (length-segment (rect-right r))))

; calculate the area of a rectangle (any representation)
(define (rect-area r)
  (* (rect-height r) (rect-width r)))

(define r
  (make-rect
    (make-segment (make-point 0 5) (make-point 10 5))     ; top
    (make-segment (make-point 0 0) (make-point 10 0))     ; bottom
    (make-segment (make-point 0 0) (make-point 0 5))      ; left
    (make-segment (make-point 10 5) (make-point 10 0))))  ; right


(display (rect-perimeter r)) (newline) ; 30
(display (rect-area r)) (newline) ; 50

