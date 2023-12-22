; to keep things simple, the coefficients are represented as primitive numbers
(define (make-poly variable term-list)
  (cons variable term-list))

(define (variable p) (car p))
(define (term-list p) (cdr p))
(define (variable? x) (symbol? x))
(define (the-empty-termlist) '())
(define (first-term term-list) (car term-list))
(define (rest-terms term-list) (cdr term-list))
(define (empty-termlist? term-list) (null? term-list))

(define (make-term order coeff) (list order coeff))
(define (order term) (car term))
(define (coeff term) (cadr term))

(define (same-variable? v1 v2)
  (and (variable? v1) (variable? v2) (eq? v1 v2)))

; adjoining terms
(define (adjoin-term term term-list)
  (cond ((and (number? (coeff term)) (= 0 (coeff term))) term-list)
        ((empty-termlist? term-list) term-list)
        ((null? term-list) (list term))
        ((> (order (car term-list)) (order term))
         (cons (car term-list) (adjoin-term term (cdr term-list))))
        ((= (order (car term-list)) (order term))
         (adjoin-term (make-term (order term)
                                 (+ (coeff term) (coeff (car term-list))))
                      (cdr term-list)))
        (else (cons term term-list))))

(define (before? v1 v2)
  (string<? (symbol->string v1) (symbol->string v2)))

(define (append-poly var number)
  (make-poly var (adjoin-term (make-term 0 number) (the-empty-termlist))))

; rewritten polynomial addition procedure
(define (add-poly p1 p2)
  (let ((v1 (variable p1))
        (v2 (variable p2))
        (t1 (term-list p1))
        (t2 (term-list p2)))
    (cond ((same-variable? v1 v2) (make-poly v1 (add-terms t1 t2)))
          ((before? v1 v2) (add-poly p1 (append-poly v1 p2)))
          (else
            (add-poly (append-poly v2 p1) p2)))))

; rewritten polynomial multiplication procedure
(define (mul-poly p1 p2)
  (let ((v1 (variable p1))
        (v2 (variable p2))
        (t1 (term-list p1))
        (t2 (term-list p2)))
    (cond ((same-variable? v1 v2) (make-poly v1 (mul-terms t1 t2)))
          ((before? v1 v2) (mul-poly p1 (append-poly v1 p2)))
          (else
            (mul-poly (append-poly v2 p1) p2)))))

; adding terms
(define (add-terms L1 L2)
  (cond ((empty-termlist? L1) L2)
        ((empty-termlist? L2) L1)
        (else
          (let ((t1 (first-term L1))
                (t2 (first-term L2)))
            (cond ((> (order t1) (order t2))
                   (adjoin-term
                     t1 (add-terms (rest-terms L1) L2)))
                  ((> (order t2) (order t1))
                   (adjoin-term
                     t2 (add-terms L1 (rest-terms L2))))
                  (else
                    (adjoin-term
                      (make-term (order t1)
                                 (+ (coeff t1) (coeff t2)))
                      (add-terms (rest-terms L1)
                                 (rest-terms L2)))))))))

; multiplying terms
(define (mul-terms L1 L2)
  (if (empty-termlist? L1)
    (the-empty-termlist)
    (add-terms (mul-terms-by-all-terms (first-term L1) L2)
               (mul-terms (rest-terms L1) L2))))

(define (mul-terms-by-all-terms t1 L)
  (if (empty-termlist? L)
    (the-empty-termlist)
    (let ((t2 (first-term L)))
      (adjoin-term
        (make-term (+ (order t1) (order t2))
                   (* (coeff t1) (coeff t2)))
        (mul-terms-by-all-terms t1 (rest-terms L))))))

; a few tests
(define p1 (make-poly 'x '((100 1) (2 2) (0 1))))
(define p2 (make-poly 'y '((55 5) (3 2) (1 1))))

; test addition of polynomials
(display (add-poly p1 p2)) (newline)

; test multiplication of polynomials
(display (mul-poly p1 p2)) (newline)
