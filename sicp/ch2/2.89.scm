; first-term needs to be re-written to also include the order
; based on the length of the term-list
(define (first-term term-list)
  (make-term (- (length term-list) 1) (car term-list)))

; changes on adjoin-term based on this new representation
(define (adjoin-term term term-list)
  (cond ((=zero? (coeff term)) term-list)
        ((= (order term) (length term-list))
         (cons (coeff term) term-list))
        (else
          (adjoin-term term (cons 0 term-list)))))

; everything else stays the same
(define (the-empty-termlist) '())
(define (variable p) (car p))
(define (term-list p) (cdr p))
(define (variable? x) (symbol? x))
(define (same-variable? v1 v2)
  (and (variable? v1) (variable? v2) (eq? v1 v2)))

(define (rest-terms term-list) (cdr term-list))
(define (empty-termlist? term-list) (null? term-list))
(define (make-term order coeff) (list order coeff))
(define (order term) (car term))
(define (coeff term) (cadr term))

; using this procedure since we are not dealing with the packages in this exercise
(define (=zero? x) (= x 0))

; a few tests to make sure that it works
(define tl (list 3))
(define t1 (make-term 1 -5))
(define t2 (make-term 2 5))
(define t3 (make-term 3 4))

(display
  (adjoin-term t3
               (adjoin-term t2
                            (adjoin-term t1 tl)))) (newline)
