(define (filter pred? seq)
  (cond ((null? seq) nil)
        ((pred? (car seq))
         (cons (car seq) (filter pred? (cdr seq))))
        (else
          (filter pred? (cdr seq)))))

(define nil '())

(define (accumulate op initial sequence)
  (if (null? sequence)
    initial
    (op (car sequence) (accumulate op initial (cdr sequence)))))

(define (enumerate-interval low high)
  (if (> low high)
    nil
    (cons low (enumerate-interval (+ low 1) high))))

(define (flatmap proc seq)
  (accumulate append nil (map proc seq)))

(define (nth-element n seq)
  (cond ((null? seq) nil)
        ((= n 0) (car seq))
        (else (nth-element (- n 1) (cdr seq)))))

(define (remove-at pos seq)
  (define (loop i seq)
    (cond ((null? seq) nil)
          ((not (= pos i))
           (cons (car seq) (loop (+ i 1) (cdr seq))))
          (else
            (loop (+ i 1) (cdr seq)))))
  (loop 0 seq))

; our procedures for the n-queens problem
(define empty-board nil)

(define (queens board-size)
  (define (queen-cols k)
    (if (= k 0)
      (list empty-board)
      (filter
        (lambda (positions) (safe? k positions))
        (flatmap
          (lambda (rest-of-queens)
            (map (lambda (new-row)
                   (adjoin-position new-row k rest-of-queens))
                 (enumerate-interval 1 board-size)))
          (queen-cols (- k 1))))))
  (queen-cols board-size))

(define (safe? k positions)
  (define (attacks? x1 y1 x2 y2)
    (or (= x1 x2)
        (= y1 y2)
        (= (abs (- x1 x2)) (abs (- y1 y2)))))
  (let ((n (nth-element (- k 1) positions)))
    (define (iter i seq)
      (cond ((or (null? seq) (> i (- k 1))) #t)
            ((attacks? n k (car seq) i) #f)
            (else (iter (+ i 1) (cdr seq)))))
      (iter 1 (remove-at (- k 1) positions))))

(define (adjoin-position new-row k rest-of-queens)
  (if (= k 1)
    (append (list new-row) rest-of-queens)
    (cons (car rest-of-queens) (adjoin-position new-row (- k 1) (cdr rest-of-queens)))))

(display (length (queens 8))) (newline)
(display (length (queens 9))) (newline)
(display (length (queens 10))) (newline)
(display (length (queens 11))) (newline)
(display (length (queens 12))) (newline)
