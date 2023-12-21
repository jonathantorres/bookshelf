;; table operations
(define (assoc key records)
  (cond ((null? records) #f)
        ((equal? key (caar records)) (car records))
        (else (assoc key (cdr records)))))

(define (make-table)
  (let ((local-table (list '*table*)))
    (define (lookup key-1 key-2)
      (let ((subtable (assoc key-1 (cdr local-table))))
        (if subtable
            (let ((record (assoc key-2 (cdr subtable))))
              (if record
                  (cdr record)
                  #f))
            #f)))
    (define (insert! key-1 key-2 value)
      (let ((subtable (assoc key-1 (cdr local-table))))
        (if subtable
            (let ((record (assoc key-2 (cdr subtable))))
              (if record
                  (set-cdr! record value)
                  (set-cdr! subtable
                            (cons (cons key-2 value)
                                  (cdr subtable)))))
            (set-cdr! local-table
                      (cons (list key-1
                                  (cons key-2 value))
                            (cdr local-table)))))
      'ok)
    (define (dispatch m)
      (cond ((eq? m 'lookup-proc) lookup)
            ((eq? m 'insert-proc!) insert!)
            (else (error "Unknown operation -- TABLE" m))))
    dispatch))

(define operation-table (make-table))
(define get (operation-table 'lookup-proc))
(define put (operation-table 'insert-proc!))

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

; in order to support any representation for complex number
; we need generic procedures for cosine, sine, square, square-root and arctangent
; and use these procedures for the complex representations (polar and rectangular)
(define (add x y) (apply-generic 'add x y))
(define (sub x y) (apply-generic 'sub x y))
(define (mul x y) (apply-generic 'mul x y))
(define (div x y) (apply-generic 'div x y))
(define (equ? x y) (apply-generic 'equ? x y))
(define (raise x) (apply-generic 'raise x))
(define (project x) (apply-generic 'project x))
(define (cosine x) (apply-generic 'cosine x))
(define (sine x) (apply-generic 'sine x))
(define (arc x y) (apply-generic 'arc x y))
(define (square x) (apply-generic 'square x))
(define (square-root x) (apply-generic 'square-root x))

; the scheme-number package
(define (install-scheme-number-package)
  (define (tag x)
    (attach-tag 'scheme-number x))
  (put 'add '(scheme-number scheme-number)
       (lambda (x y) (tag (+ x y))))
  (put 'sub '(scheme-number scheme-number)
       (lambda (x y) (tag (- x y))))
  (put 'mul '(scheme-number scheme-number)
       (lambda (x y) (tag (* x y))))
  (put 'div '(scheme-number scheme-number)
       (lambda (x y) (tag (/ x y))))
  (put 'equ? '(scheme-number scheme-number)
       (lambda (x y) (= x y)))
  (put 'raise '(scheme-number)
       (lambda (x) (make-rational x 1)))
  (put 'project '(scheme-number)
       (lambda (x) (tag x)))
  (put 'cosine '(scheme-number)
       (lambda (x) (tag (cos x))))
  (put 'sine '(scheme-number)
       (lambda (x) (tag (sin x))))
  (put 'arc '(scheme-number scheme-number)
       (lambda (x y) (tag (atan x y))))
  (put 'square '(scheme-number)
       (lambda (x) (tag (* x x))))
  (put 'square-root '(scheme-number)
       (lambda (x) (tag (sqrt x))))
  (put 'make 'scheme-number
       (lambda (x) (tag x)))
  'done)

(define (make-scheme-number n)
  ((get 'make 'scheme-number) n))

; the rational number package
(define (install-rational-package)
  ;; internal procedures
  (define (numer x) (car x))
  (define (denom x) (cdr x))
  (define (make-rat n d)
    (let ((g (gcd n d)))
      (cons (/ n g) (/ d g))))
  (define (add-rat x y)
    (make-rat (+ (* (numer x) (denom y))
                 (* (numer y) (denom x)))
              (* (denom x) (denom y))))
  (define (sub-rat x y)
    (make-rat (- (* (numer x) (denom y))
                 (* (numer y) (denom x)))
              (* (denom x) (denom y))))
  (define (mul-rat x y)
    (make-rat (* (numer x) (numer y))
              (* (denom x) (denom y))))
  (define (div-rat x y)
    (make-rat (* (numer x) (denom y))
              (* (denom x) (numer y))))
  (define (equ? x y)
    (= (* (numer x) (denom y)) (* (numer y) (denom x))))

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
  (put 'equ? '(rational rational)
       (lambda (x y) (equ? x y)))
  (put 'raise '(rational)
       (lambda (x) (make-complex-from-real-imag
                     (make-scheme-number (* 1.0 (/ (numer x) (denom x))))
                     (make-scheme-number 0))))
  (put 'project '(rational)
       (lambda (x)
         (if (= 1 (denom x))
           (make-scheme-number (numer x))
           (tag x))))
  (put 'cosine '(rational)
       (lambda (x) (make-scheme-number (cos (/ (numer x) (denom x))))))
  (put 'sine '(rational)
       (lambda (x) (make-scheme-number (sin (/ (numer x) (denom x))))))
  (put 'arc '(rational rational)
       (lambda (x y) (make-scheme-number (atan (/ (numer x) (denom x)) (/ (numer y) (denom y))))))
  (put 'square '(rational)
       (lambda (x) (tag (mul-rat x x))))
  (put 'square-root '(rational)
       (lambda (x) (make-scheme-number (sqrt (/ (* 1.0 (numer x)) (denom x))))))
  (put 'make 'rational
       (lambda (n d) (tag (make-rat n d))))
  'done)

(define (make-rational n d)
  ((get 'make 'rational) n d))

; rectangular representation for complex numbers using generic mathematical functions
(define (install-rectangular-package)
  ;; internal procedures
  (define (real-part z) (car z))
  (define (imag-part z) (cdr z))
  (define (make-from-real-imag x y) (cons x y))
  (define (magnitude z)
    (square-root (add (square (real-part z))
             (square (imag-part z)))))
  (define (angle z)
    (arc (imag-part z) (real-part z)))
  (define (make-from-mag-ang r a) 
    (cons (mul r (cosine a)) (mul r (sine a))))

  ;; interface to the rest of the system
  (define (tag x) (attach-tag 'rectangular x))
  (put 'real-part '(rectangular) real-part)
  (put 'imag-part '(rectangular) imag-part)
  (put 'magnitude '(rectangular) magnitude)
  (put 'angle '(rectangular) angle)
  (put 'make-from-real-imag 'rectangular
       (lambda (x y) (tag (make-from-real-imag x y))))
  (put 'make-from-mag-ang 'rectangular
       (lambda (r a) (tag (make-from-mag-ang r a))))
  'done)

; polar representation for complex numbers using generic mathematical functions
(define (install-polar-package)
  ;; internal procedures
  (define (magnitude z) (car z))
  (define (angle z) (cdr z))
  (define (make-from-mag-ang r a) (cons r a))
  (define (real-part z)
    (mul (magnitude z) (cosine (angle z))))
  (define (imag-part z)
    (mul (magnitude z) (sine (angle z))))
  (define (make-from-real-imag x y) 
    (cons (square-root (add (square x) (square y)))
          (arc y x)))

  ;; interface to the rest of the system
  (define (tag x) (attach-tag 'polar x))
  (put 'real-part '(polar) real-part)
  (put 'imag-part '(polar) imag-part)
  (put 'magnitude '(polar) magnitude)
  (put 'angle '(polar) angle)
  (put 'make-from-real-imag 'polar
       (lambda (x y) (tag (make-from-real-imag x y))))
  (put 'make-from-mag-ang 'polar
       (lambda (r a) (tag (make-from-mag-ang r a))))
  'done)

; the complex number package using generic mathematical functions
(define (install-complex-package)
  ;; imported procedures from rectangular and polar packages
  (define (make-from-real-imag x y)
    ((get 'make-from-real-imag 'rectangular) x y))

  (define (make-from-mag-ang r a)
    ((get 'make-from-mag-ang 'polar) r a))

  ;; internal procedures
  (define (real-part z)
    (apply-generic 'real-part z))
  (define (imag-part z)
    (apply-generic 'imag-part z))
  (define (magnitude z)
    (apply-generic 'magnitude z))
  (define (angle z)
    (apply-generic 'angle z))
  (define (add-complex z1 z2)
    (make-from-real-imag (add (real-part z1) (real-part z2))
                         (add (imag-part z1) (imag-part z2))))
  (define (sub-complex z1 z2)
    (make-from-real-imag (sub (real-part z1) (real-part z2))
                         (sub (imag-part z1) (imag-part z2))))
  (define (mul-complex z1 z2)
    (make-from-mag-ang (mul (magnitude z1) (magnitude z2))
                       (add (angle z1) (angle z2))))
  (define (div-complex z1 z2)
    (make-from-mag-ang (div (magnitude z1) (magnitude z2))
                       (sub (angle z1) (angle z2))))
  (define (equ-complex? z1 z2)
    (and (equ? (real-part z1) (real-part z2))
         (equ? (imag-part z1) (imag-part z2))))

  ;; interface to rest of the system
  (define (tag z) (attach-tag 'complex z))
  (put 'add '(complex complex)
       (lambda (z1 z2) (tag (add-complex z1 z2))))
  (put 'sub '(complex complex)
       (lambda (z1 z2) (tag (sub-complex z1 z2))))
  (put 'mul '(complex complex)
       (lambda (z1 z2) (tag (mul-complex z1 z2))))
  (put 'div '(complex complex)
       (lambda (z1 z2) (tag (div-complex z1 z2))))
  (put 'equ? '(complex complex)
       (lambda (z1 z2) (equ-complex? z1 z2)))
  (put 'project '(complex)
       (lambda (z)
         (if (equ? (make-scheme-number 0) (imag-part z))
           (make-rational (real-part z) 1)
           (tag z))))
  (put 'make-from-real-imag 'complex
       (lambda (x y) (tag (make-from-real-imag x y))))
  (put 'make-from-mag-ang 'complex
       (lambda (r a) (tag (make-from-mag-ang r a))))
  'done)

(define (make-complex-from-real-imag x y)
  ((get 'make-from-real-imag 'complex) x y))

(define (make-complex-from-mag-ang r a)
  ((get 'make-from-mag-ang 'complex) r a))

; hierarchy of types
(define hierarchy (list 'scheme-number 'rational 'complex))

; our "drop" procedure to attempt to drop a type down in the hierarchy as low as possible
(define (drop type)
  (define (scheme-number? x) (equal? (type-tag x) 'scheme-number))
  (if (scheme-number? type)
    type
    (let ((projected (project type)))
      (if (and
            (not (equal? (type-tag type) (type-tag projected)))
            (equ? (raise projected) type))
        (drop projected)
        type))))

; procedure to get the level of a type in the hierarchy
(define (level type type-list)
  (cond ((null? type-list)
         (error "type is not supported" type))
        ((equal? type (car type-list)) 1)
        (else
          (+ 1 (level type (cdr type-list))))))

; procedure to raise a type to the next level of the hierarchy
(define (succesive-raising type to-type-tag)
  (if (= (level (type-tag type) hierarchy) (level to-type-tag hierarchy))
    type
    (succesive-raising (raise type) to-type-tag)))

; check if the operation needs to be simplified
(define (simplify? op)
  (if (or
        (equal? op 'add)
        (equal? op 'sub)
        (equal? op 'mul)
        (equal? op 'div))
    #t
    #f))

(define (apply-generic op . args)
  (let ((type-tags (map type-tag args)))
    (let ((proc (get op type-tags)))
      (if proc
        (if (simplify? op)
          (drop (apply proc (map contents args)))
          (apply proc (map contents args)))
        (if (= (length args) 2)
          (let ((type1 (car type-tags))
                (type2 (cadr type-tags))
                (a1 (car args))
                (a2 (cadr args)))
            (cond ((> (level type1 hierarchy) (level type2 hierarchy))
                   (apply-generic op a1 (succesive-raising a2 type1)))
                  ((> (level type2 hierarchy) (level type1 hierarchy))
                   (apply-generic op (succesive-raising a1 type2) a2))
                  (else
                    (error "No method for these types" (list op type-tags)))))
          (error "No method for these types"
                 (list op type-tags)))))))

; install packages
(install-scheme-number-package)
(install-rational-package)
(install-rectangular-package)
(install-polar-package)
(install-complex-package)

(define a (make-complex-from-real-imag (make-scheme-number 10) (make-rational 5 1)))
(define b (make-complex-from-real-imag (make-rational 8 2) (make-scheme-number 4)))

(display (add a b)) (newline)
(display (sub a b)) (newline)
(display (mul a b)) (newline)
(display (div a b)) (newline)
