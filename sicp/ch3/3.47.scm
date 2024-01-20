(define (test-and-set! cell)
  (if (car cell)
    #t
    (begin (set-car! cell #t)
           #f)))

(define (clear! cell)
  (set-car! cell #f))

(define (make-mutex)
  (let ((cell (list #f)))
    (define (the-mutex m)
      (cond ((eq? m 'acquire)
             (if (test-and-set! cell)
               (the-mutex 'acquire)))
            ((eq? m 'release) (clear! cell))))
    the-mutex))

; a) A semaphore based on mutexes
(define (make-sem-m n)
  (let ((n n)
        (mu (make-mutex)))
    (define (sem m)
      (cond ((eq? m 'acquire)
             (mu 'acquire)
             (if (< n 0)
               (begin
                 (mu 'release)
                 (sem 'acquire))
               (begin
                 (set! n (- n 1))
                 (mu 'release))))
            ((eq? m 'release)
             (mu 'acquire)
             (set! n (+ n 1))
             (mu 'release))))
    sem))

; b) A semaphore using test-and-set!
(define (make-sem n)
  (let ((n n)
        (cell (list #f)))
    (define (sem m)
      (cond ((eq? m 'acquire)
             (if (test-and-set! cell)
               (sem 'acquire)
               (begin
                 (if (< n 0)
                   (begin
                     (clear! cell)
                     (sem 'acquire))
                   (begin
                     (set! n (- n 1))
                     (clear! cell))))))
            ((eq? m 'release)
             (if (test-and-set! cell)
               (sem 'release)
               (begin
                 (set! n (+ n 1))
                 (clear! cell))))))
             
    sem))

