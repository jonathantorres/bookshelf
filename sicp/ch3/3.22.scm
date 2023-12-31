(define (make-queue)
  (let ((front-ptr '())
        (rear-ptr '()))
    ;; internal procedures
    (define (set-front-ptr! item) (set! front-ptr item))
    (define (set-rear-ptr! item) (set! rear-ptr item))
    (define (print-queue)
      (display front-ptr)
      (newline))
    (define (empty-queue?)
      (null? front-ptr))
    (define (front-queue)
      (if (empty-queue?)
        (error ("FRONT called with an empty queue" front-ptr))
        (car front-ptr)))
    (define (insert-queue! item)
      (let ((new-pair (cons item '())))
        (cond ((empty-queue?)
               (set-front-ptr! new-pair)
               (set-rear-ptr! new-pair)
               'done)
              (else
                (set-cdr! rear-ptr new-pair)
                (set-rear-ptr! new-pair)
                'done))))
    (define (delete-queue!)
      (cond ((empty-queue?)
             (error "DELETE! called with an empty queue" front-ptr))
            (else
              (set-front-ptr! (cdr front-ptr))
              'done)))
               
    (define (dispatch m)
      (cond ((eq? m 'print-queue) print-queue)
            ((eq? m 'empty-queue?) empty-queue?)
            ((eq? m 'front-queue) front-queue)
            ((eq? m 'insert-queue!) insert-queue!)
            ((eq? m 'delete-queue!) delete-queue!)
            (else
              (error "invalid operation" m))))
    dispatch))

(define (print-queue queue)
  ((queue 'print-queue)))

(define (empty-queue? queue)
  ((queue 'empty-queue?)))

(define (front-queue queue)
  ((queue 'front-queue)))

(define (insert-queue! queue item)
  ((queue 'insert-queue!) item))

(define (delete-queue! queue)
  ((queue 'delete-queue!)))

; tests
(define q1 (make-queue))

(insert-queue! q1 'a)
(print-queue q1)

(insert-queue! q1 'b)
(print-queue q1)

(delete-queue! q1)
(print-queue q1)

(delete-queue! q1)
(print-queue q1)

