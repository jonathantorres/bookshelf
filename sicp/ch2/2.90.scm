(include "table.scm")

; tagging procedures
(define (attach-tag type-tag contents)
  (cons type-tag contents))

(define (type-tag datum)
  (if (pair? datum)
      (car datum)
      (error "Bad tagged datum -- TYPE-TAG" datum)))

(define (contents datum)
  (if (pair? datum)
      (cdr datum)
      (error "Bad tagged datum -- CONTENTS" datum)))

(define (apply-generic op . args)
  (let ((type-tags (map type-tag args)))
    (let ((proc (get op type-tags)))
      (if proc
          (apply proc (map contents args))
          (error
            "No method for these types -- APPLY-GENERIC"
            (list op type-tags))))))

; to keep things simple, I decided to use
; primitive numbers to represent the polynomial's coefficients

; generic procedures
(define (add x y) (apply-generic 'add x y))
(define (sub x y) (apply-generic 'sub x y))
(define (mul x y) (apply-generic 'mul x y))
(define (div x y) (apply-generic 'div x y))

; sparse representation of polynomials
(define (install-sparse-package)
  ; internal procedures
  (define (first-term term-list) (car term-list))
  (define (rest-terms term-list) (cdr term-list))
  (define (empty-termlist? term-list) (null? term-list))
  (define (the-empty-termlist) '())
  (define (coeff term) (cadr term))

  ; adjoining terms
  (define (adjoin-term term term-list)
    (if (= 0 (coeff term))
      term-list
      (cons term term-list)))

  (define (make-sparse-poly variable term-list)
    (cons variable term-list))

  ; interface to the rest of the system
  (define (tag x) (attach-tag 'sparse x))
  (put 'first-term '(sparse)
       (lambda (tl) (first-term tl)))
  (put 'rest-terms '(sparse)
       (lambda (tl) (tag (rest-terms tl))))
  (put 'empty-termlist? '(sparse)
       (lambda (tl) (empty-termlist? tl)))
  (put 'the-empty-termlist 'sparse
       (lambda () (tag (the-empty-termlist))))
  (put 'adjoin-term 'sparse
       (lambda (t tl) (tag (adjoin-term t tl))))
  (put 'make-sparse-poly 'sparse
       (lambda (var terms) (make-sparse-poly var (tag terms))))
  'done)

; dense representation of polynomials
(define (install-dense-package)
  ; internal procedures
  (define (make-term order coeff) (list order coeff))
  (define (first-term term-list)
    (make-term (- (length term-list) 1) (car term-list)))
  (define (rest-terms term-list) (cdr term-list))
  (define (empty-termlist? term-list) (null? term-list))
  (define (the-empty-termlist) '())
  (define (order term) (car term))
  (define (coeff term) (cadr term))

  ; adjoining terms
  (define (adjoin-term term term-list)
    (cond ((= 0 (coeff term)) term-list)
          ((= (order term) (length term-list))
           (cons (coeff term) term-list))
          (else
            (adjoin-term term (cons 0 term-list)))))

  (define (make-dense-poly variable term-list)
    (cons variable term-list))

  ; interface to the rest of the system
  (define (tag x) (attach-tag 'dense x))
  (put 'first-term '(dense)
       (lambda (tl) (first-term tl)))
  (put 'rest-terms '(dense)
       (lambda (tl) (tag (rest-terms tl))))
  (put 'empty-termlist? '(dense)
       (lambda (tl) (empty-termlist? tl)))
  (put 'the-empty-termlist 'dense
       (lambda () (tag (the-empty-termlist))))
  (put 'adjoin-term 'dense
       (lambda (t tl) (tag (adjoin-term t tl))))
  (put 'make-dense-poly 'dense
       (lambda (var terms) (make-dense-poly var (tag terms))))
  'done)

; the polynomial package
(define (install-polynomial-package)
  ; imported procedures from sparse and dense packages
  (define (make-sparse-poly var terms)
    ((get 'make-sparse-poly 'sparse) var terms))

  (define (make-dense-poly var terms)
    ((get 'make-dense-poly 'dense) var terms))

  ; internal procedures
  (define (make-term order coeff) (list order coeff))
  (define (order term) (car term))
  (define (coeff term) (cadr term))
  (define (variable p) (car p))
  (define (term-list p) (cdr p))
  (define (variable? x) (symbol? x))
  (define (same-variable? v1 v2)
    (and (variable? v1) (variable? v2) (eq? v1 v2)))
  (define (first-term tl)
    (apply-generic 'first-term tl))
  (define (rest-terms tl)
    (apply-generic 'rest-terms tl))
  (define (empty-termlist? tl)
    (apply-generic 'empty-termlist? tl))
  (define (the-empty-termlist tl)
    ((get 'the-empty-termlist (type-tag tl))))

  (define (adjoin-term term term-list)
    (let ((proc (get 'adjoin-term (type-tag term-list))))
      (if proc
        (proc term (contents term-list))
        (error "No method for these types - ADJOIN-TERM" term-list))))

  (define (make-poly variable term-list)
    (cons variable term-list))

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
      (the-empty-termlist L1)
      (add-terms (mul-terms-by-all-terms (first-term L1) L2)
                 (mul-terms (rest-terms L1) L2))))

  (define (mul-terms-by-all-terms t1 L)
    (if (empty-termlist? L)
      (the-empty-termlist L)
      (let ((t2 (first-term L)))
        (adjoin-term
          (make-term (+ (order t1) (order t2))
                     (* (coeff t1) (coeff t2)))
          (mul-terms-by-all-terms t1 (rest-terms L))))))

  ; polynomial addition
  (define (add-poly p1 p2)
    (if (same-variable? (variable p1) (variable p2))
      (make-poly (variable p1)
                 (add-terms (term-list p1)
                            (term-list p2)))
      (error "Polys not in same var -- ADD-POLY"
             (list p1 p2))))

  ; polynomial multiplication
  (define (mul-poly p1 p2)
    (if (same-variable? (variable p1) (variable p2))
      (make-poly (variable p1)
                 (mul-terms (term-list p1)
                            (term-list p2)))
      (error "Polys not in same var -- MUL-POLY"
             (list p1 p2))))

  ; interface to the rest of the system
  (define (tag p) (attach-tag 'polynomial p))
  (put 'add '(polynomial polynomial)
       (lambda (p1 p2) (tag (add-poly p1 p2))))
  (put 'mul '(polynomial polynomial)
       (lambda (p1 p2) (tag (mul-poly p1 p2))))
  (put 'make-sparse 'polynomial
       (lambda (var terms) (tag (make-sparse-poly var terms))))
  (put 'make-dense 'polynomial
       (lambda (var terms) (tag (make-dense-poly var terms))))
  'done)

(define (make-sparse-poly var terms)
  ((get 'make-sparse 'polynomial) var terms))

(define (make-dense-poly var terms)
  ((get 'make-dense 'polynomial) var terms))

; install packages
(install-sparse-package)
(install-dense-package)
(install-polynomial-package)

(define p1 (make-sparse-poly 'x '((100 1) (2 2) (0 1))))
(define p2 (make-dense-poly 'x '(0 3 4 2)))

(display (add p1 p1)) (newline)
(display (mul p1 p1)) (newline)
(display (add p2 p2)) (newline)
(display (mul p2 p2)) (newline)
