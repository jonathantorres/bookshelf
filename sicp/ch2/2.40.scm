(define nil '())

(define (accumulate op initial sequence)
  (if (null? sequence)
    initial
    (op (car sequence) (accumulate op initial (cdr sequence)))))

(define (flatmap proc seq)
  (accumulate append nil (map proc seq)))

(define (enumerate-interval low high)
  (if (> low high)
    nil
    (cons low (enumerate-interval (+ low 1) high))))

(define (filter pred? seq)
  (cond ((null? seq) nil)
        ((pred? (car seq))
         (cons (car seq) (filter pred? (cdr seq))))
        (else
          (filter pred? (cdr seq)))))

(define (make-pair-sum p)
  (list (car p) (cadr p) (+ (car p) (cadr p))))

(define (prime-sum? p)
  (prime? (+ (car p) (cadr p))))

; prime procedure using the fermat test from chapter 1
(define (prime? n)
  (define (fast-prime? n times)
    (cond ((= times 0) #t)
          ((fermat-test n) (fast-prime? n (- times 1)))
          (else #f)))
  (define (fermat-test n)
    (define (try-it a)
      (= (expmod a n n) a))
    (try-it (+ 1 (random (- n 1)))))
  (define (square x)
    (* x x))
  (define (expmod base exp m)
    (cond ((= exp 0) 1)
          ((even? exp)
           (remainder (square (expmod base (/ exp 2) m)) m))
          (else
            (remainder (* base (expmod base (- exp 1) m)) m))))
  (fast-prime? n 10))

; our unique-pairs procedure
(define (unique-pairs n)
  (flatmap (lambda (i)
             (map
               (lambda (j) (list i j))
               (enumerate-interval 1 (- i 1))))
           (enumerate-interval 1 n)))

; prime-sum-pairs that uses the unique-pairs procedure
(define (prime-sum-pairs n)
  (map make-pair-sum
       (filter prime-sum? (unique-pairs n))))

(display (prime-sum-pairs 6)) (newline)

