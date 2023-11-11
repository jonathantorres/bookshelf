; recursive version that uses append
(define (reverse l)
  (if (null? (cdr l))
    l
    (append (reverse (cdr l)) (list (car l)))))

(define nil '())

; iterative version
(define (reverse-iter l)
  (define (iter lst r)
    (if (null? lst)
      r
      (iter (cdr lst) (cons (car lst) r))))
  (iter l nil))

(define (append list1 list2)
  (if (null? list1)
    list2
    (cons (car list1) (append (cdr list1) list2))))

(display (reverse (list 1 4 9 16 25))) (newline)
(display (reverse-iter (list 1 4 9 16 25))) (newline)

