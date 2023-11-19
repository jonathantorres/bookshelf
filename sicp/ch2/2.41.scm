(define nil '())

; support procedures (accumulate, flatmap and others)
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

; our ordered triples procedure
(define (ord-triples n s)
  (define (add-to-s? t)
    (= s (accumulate + 0 t)))
  (filter
    add-to-s?
    (flatmap (lambda (i)
               (flatmap (lambda (j)
                          (map (lambda (k)
                                 (list i j k))
                               (enumerate-interval 1 (- j 1))))
                        (enumerate-interval 1 (- i 1))))
             (enumerate-interval 1 n))))

(display (ord-triples 6 10)) (newline)
