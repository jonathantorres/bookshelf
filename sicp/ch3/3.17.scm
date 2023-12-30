; broken version
(define (count-pairs-bad x)
  (if (not (pair? x))
    0
    (+
      (count-pairs-bad (car x))
      (count-pairs-bad (cdr x))
      1)))

; our correct version
(define (count-pairs x)
  (define seen '())
  (define (last-pair x)
    (if (null? (cdr x))
      x
      (last-pair (cdr x))))
  (define (append! x y)
    (set-cdr! (last-pair x) y))
  (define (already-seen? seen x)
    (cond ((null? seen) #f)
          ((eq? (car seen) x) #t)
          (else
            (already-seen? (cdr seen) x))))
  (define (loop x)
    (cond ((and (pair? x) (not (already-seen? seen x)))
           (begin
             (if (null? seen)
               (set! seen (cons x '()))
               (append! seen (cons x '())))
               (loop (car x))
               (loop (cdr x))))
          (else
            seen)))
  (begin
    (loop x)
    (length seen)))

(define x (list 2 3))
(define y (list 3))
(define z (cons y y))

(define a (list 1 2 3))
(define b (cons x (cdr x)))
(define c (cons z z))
(define d (list 1 2 3))
(set-cdr! (cddr d) d)

(display (count-pairs-bad a)) (newline) ; 3
(display (count-pairs-bad b)) (newline) ; 4
(display (count-pairs-bad c)) (newline) ; 7
; (display (count-pairs-bad d)) (newline) ; infinite loop

(display "---------------") (newline)

(display (count-pairs a)) (newline) ; 3
(display (count-pairs b)) (newline) ; 3
(display (count-pairs c)) (newline) ; 3
(display (count-pairs d)) (newline) ; 3
