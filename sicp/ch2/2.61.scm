(define (element-of-set? x set)
  (cond ((null? set) #f)
        ((= x (car set)) #t)
        ((< x (car set)) #f)
        (else (element-of-set? x (cdr set)))))

(define (adjoin-set x set)
  (cond ((or (null? set) (< x (car set)))
         (cons x set))
        ((= x (car set)) set)
        (else
          (cons (car set) (adjoin-set x (cdr set))))))

(define x (list 1 2 3 4))
(define y (list 3 4 5 6))

(display (element-of-set? 1 (list 1 2 3))) (newline) ; #t
(display (element-of-set? 5 (list 1 2 3))) (newline) ; #f
(display (adjoin-set 1 (list 1 2 3))) (newline)      ; (1 2 3)
(display (adjoin-set 1 (list 2 3 4))) (newline)      ; (1 2 3 4)
(display (adjoin-set 4 (list 1 2 3))) (newline)      ; (1 2 3 4)
(display (adjoin-set 4 (list 1 2 3 5))) (newline)    ; (1 2 3 4 5)
