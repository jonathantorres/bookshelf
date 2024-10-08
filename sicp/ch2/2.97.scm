(include "table.scm")

; tagging procedures
(define (attach-tag type-tag contents)
  (if (eq? type-tag 'number)
      contents
      (cons type-tag contents)))

(define (type-tag datum)
  (cond ((number? datum) 'number)
        ((pair? datum) (car datum))
        (else (error "Bad tagged datum - TYPE-TAG" datum))))

(define (contents datum)
  (cond ((number? datum) datum)
        ((pair? datum) (cdr datum))
        (else (error "Bad tagged datum - CONTENTS" datum))))

(define (apply-generic op . args)
  (let ((type-tags (map type-tag args)))
    (let ((proc (get op type-tags)))
      (if proc
          (apply proc (map contents args))
          (error
            "No method for these types -- APPLY-GENERIC"
            (list op type-tags))))))

; generic procedures
(define (add x y) (apply-generic 'add x y))
(define (sub x y) (apply-generic 'sub x y))
(define (mul x y) (apply-generic 'mul x y))
(define (div x y) (apply-generic 'div x y))
(define (equ? x y) (apply-generic 'equ? x y))
(define (neg x) (apply-generic 'neg x))
(define (=zero? x) (apply-generic '=zero? x))
(define (greatest-common-divisor x y) (apply-generic 'greatest-common-divisor x y))
(define (reduce x y) (apply-generic 'reduce x y))

; the scheme number package
(define (install-scheme-number-package)
  ; b: reduce integers
  (define (reduce-integers n d)
    (let ((g (gcd n d)))
      (list (/ n g) (/ d g))))

  (put 'add '(number number) +)
  (put 'sub '(number number) -)
  (put 'mul '(number number) *)
  (put 'div '(number number) /)
  (put 'neg '(number) -)
  (put 'equ? '(number number) =)
  (put '=zero? '(number) zero?)
  (put 'greatest-common-divisor '(number number) gcd)
  (put 'reduce '(number number) reduce-integers)
  'done')

; the rational number package
(define (install-rational-package)
  ;; internal procedures
  (define (numer x) (car x))
  (define (denom x) (cdr x))

  ; b: use reduce before creating a rational number
  (define (make-rat n d)
    (let ((reduced (reduce n d)))
      (cons (car reduced) (cadr reduced))))

  (define (add-rat x y)
    (make-rat (add (mul (numer x) (denom y))
                 (mul (numer y) (denom x)))
              (mul (denom x) (denom y))))
  (define (sub-rat x y)
    (make-rat (sub (mul (numer x) (denom y))
                 (mul (numer y) (denom x)))
              (mul (denom x) (denom y))))
  (define (mul-rat x y)
    (make-rat (mul (numer x) (numer y))
              (mul (denom x) (denom y))))
  (define (div-rat x y)
    (make-rat (mul (numer x) (denom y))
              (mul (denom x) (numer y))))

  ;; interface to rest of the system
  (define (tag x) (attach-tag 'rational x))
  (put 'add '(rational rational)
       (lambda (x y) (tag (add-rat x y))))
  (put 'sub '(rational rational)
       (lambda (x y) (tag (sub-rat x y))))
  (put 'mul '(rational rational)
       (lambda (x y) (tag (mul-rat x y))))
  (put 'div '(rational rational)
       (lambda (x y) (tag (div-rat x y))))
  (put 'make 'rational
       (lambda (n d) (tag (make-rat n d))))
  'done)

(define (make-rational n d)
  ((get 'make 'rational) n d))

; the polynomial package
(define (install-polynomial-package)
  ; internal procedures
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
    (if (=zero? (coeff term))
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
                                   (add (coeff t1) (coeff t2)))
                        (add-terms (rest-terms L1)
                                   (rest-terms L2)))))))))

  ; polynomial subtraction
  (define (sub-poly p1 p2)
    (if (same-variable? (variable p1) (variable p2))
      (make-poly (variable p1)
                 (sub-terms (term-list p1)
                            (term-list p2)))
      (error "Polys not in same var -- SUB-POLY"
             (list p1 p2))))

  ; subtracting terms
  (define (sub-terms L1 L2)
    (define (neg-terms L)
      (if (empty-termlist? L)
        (the-empty-termlist)
        (let ((first (first-term L))
              (rest (rest-terms L)))
          (adjoin-term (make-term (order first) (neg (coeff first)))
                       (neg-terms rest)))))
    (add-terms L1 (neg-terms L2)))

  ; polynomial multiplication
  (define (mul-poly p1 p2)
    (if (same-variable? (variable p1) (variable p2))
      (make-poly (variable p1)
                 (mul-terms (term-list p1)
                            (term-list p2)))
      (error "Polys not in same var -- MUL-POLY"
             (list p1 p2))))

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
                     (mul (coeff t1) (coeff t2)))
          (mul-terms-by-all-terms t1 (rest-terms L))))))

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
          (let ((new-c (div (coeff t1) (coeff t2)))
                (new-o (sub (order t1) (order t2))))
            (let ((rest-of-result
                    (div-terms (sub-terms L1
                                          (mul-terms-by-all-terms
                                            (make-term new-o new-c)
                                            L2))
                               L2)))
              (list (adjoin-term (make-term new-o new-c)
                                 (car rest-of-result))
                    (cadr rest-of-result))))))))

  ; gcd for polynomials
  (define (gcd-poly p1 p2)
    (if (same-variable? (variable p1) (variable p2))
      (make-poly (variable p1)
                 (gcd-terms (term-list p1)
                            (term-list p2)))
      (error "Polys not in same var -- GCD-POLY"
             (list p1 p2))))

  (define (pseudoremainder-terms L1 L2)
    (let ((o1 (order (first-term L1)))
          (o2 (order (first-term L2))))
      (let ((int-factor (expt (coeff (first-term L2))
                              (+ 1 o1 (- o2)))))
        (cadr (div-terms (mul-terms-by-all-terms
                           (make-term 0 int-factor) L1)
                         L2)))))

  (define (gcd-terms a b)
    (if (empty-termlist? b)
      (let ((divisor (apply gcd (map coeff a))))
        (car (div-terms a (adjoin-term
                            (make-term 0 divisor)
                            (the-empty-termlist)))))
      (gcd-terms b (pseudoremainder-terms a b))))

  ; a: implementation of reduce-terms and reduce-poly
  (define (reduce-terms n d)
    (let ((terms (gcd-terms n d)))
      (list (car (div-terms n terms))
            (car (div-terms d terms)))))

  (define (reduce-poly p1 p2)
    (if (same-variable? (variable p1) (variable p2))
      (let ((reduced (reduce-terms (term-list p1) (term-list p2))))
        (list
          (make-poly (variable p1) (car reduced))
          (make-poly (variable p1) (cadr reduced))))
      (error "Polys not in same var -- REDUCE-POLY"
             (list p1 p2))))

  ; interface to the rest of the system
  (define (tag p) (attach-tag 'polynomial p))
  (put 'add '(polynomial polynomial)
       (lambda (p1 p2) (tag (add-poly p1 p2))))
  (put 'sub '(polynomial polynomial)
       (lambda (p1 p2) (tag (sub-poly p1 p2))))
  (put 'mul '(polynomial polynomial)
       (lambda (p1 p2) (tag (mul-poly p1 p2))))
  (put 'div '(polynomial polynomial)
       (lambda (p1 p2) (tag (div-poly p1 p2))))
  (put 'greatest-common-divisor '(polynomial polynomial)
       (lambda (p1 p2) (tag (gcd-poly p1 p2))))
  (put 'reduce '(polynomial polynomial)
       (lambda (p1 p2) (map tag (reduce-poly p1 p2))))
  (put 'make 'polynomial
       (lambda (var terms) (tag (make-poly var terms))))
  'done)

(define (make-polynomial var terms)
  ((get 'make 'polynomial) var terms))

; install packages
(install-scheme-number-package)
(install-rational-package)
(install-polynomial-package)

; test polynomials
(define p1 (make-polynomial 'x '((1 1) (0 1))))
(define p2 (make-polynomial 'x '((3 1) (0 -1))))
(define p3 (make-polynomial 'x '((1 1))))
(define p4 (make-polynomial 'x '((2 1) (0 -1))))

(define rf1 (make-rational p1 p2))
(define rf2 (make-rational p3 p4))

(display (add rf1 rf2)) (newline)
