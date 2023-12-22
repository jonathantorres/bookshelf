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
  (if (= 0 (coeff term))
    term-list
    (cons term term-list)))

; polynomial addition
(define (add-poly p1 p2)
  (if (same-variable? (variable p1) (variable p2))
    (make-poly (variable p1)
               (add-terms (term-list p1)
                          (term-list p2)))
    (error "Polys not in same var -- ADD-POLY"
           (list p1 p2))))

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

; subtracting terms
(define (sub-terms L1 L2)
  (define (neg-terms L)
    (if (empty-termlist? L)
      (the-empty-termlist)
      (let ((first (first-term L))
            (rest (rest-terms L)))
        (adjoin-term (make-term (order first) (* (coeff first) -1))
                     (neg-terms rest)))))
  (add-terms L1 (neg-terms L2)))

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

; polynomial multiplication
(define (mul-poly p1 p2)
  (if (same-variable? (variable p1) (variable p2))
    (make-poly (variable p1)
               (mul-terms (term-list p1)
                          (term-list p2)))
    (error "Polys not in same var -- MUL-POLY"
           (list p1 p2))))

; polynomial division
(define (div-poly p1 p2)
  (if (same-variable? (variable p1) (variable p2))
    (let ((result (div-terms (term-list p1) (term-list p2))))
      (let ((quotient-tl (car result))
            (remainder-tl (cadr result)))
        (list (make-poly (variable p1) quotient-tl)
              (make-poly (variable p1) remainder-tl))))
    (error "Polys not in same var -- DIV-POLY"
           (list p1 p2))))

; dividing terms
(define (div-terms L1 L2)
  (if (empty-termlist? L1)
    (list (the-empty-termlist) (the-empty-termlist))
    (let ((t1 (first-term L1))
          (t2 (first-term L2)))
      (if (> (order t2) (order t1))
        (list (the-empty-termlist) L1)
        (let ((new-c (/ (coeff t1) (coeff t2)))
              (new-o (- (order t1) (order t2))))
          (let ((rest-of-result
                  (div-terms (sub-terms L1
                                        (mul-terms-by-all-terms
                                          (make-term new-o new-c)
                                          L2))
                             L2)))
            (list (adjoin-term (make-term new-o new-c)
                               (car rest-of-result))
                  (cadr rest-of-result))))))))

; test division of polynomials
(define p1 (make-poly 'x '((100 1) (2 2) (0 1))))
(define p2 (make-poly 'x '((55 5) (3 2) (1 1))))

(display (div-poly p1 p2)) (newline)
