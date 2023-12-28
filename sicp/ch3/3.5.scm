; this is needed so that (random) works as expected
(set! *random-state* (random-state-from-platform))

(define (monte-carlo trials experiment)
  (define (iter trials-remaining trials-passed)
    (cond ((= trials-remaining 0)
           (/ trials-passed trials))
          ((experiment)
           (iter (- trials-remaining 1)
                 (+ trials-passed 1)))
          (else
            (iter (- trials-remaining 1)
                  trials-passed))))
  (iter trials 0))

(define (random-in-range low high)
  (let ((range (- high low)))
    (+ low (random range))))

(define (estimate-integral predicate x1 x2 y1 y2 trials)
  (* (* (- x2 x1)
        (- x2 x1))
     (monte-carlo trials predicate)))

(define (estimate-pi)
  (define (in-circle)
    (>= 1 (+
            (square (random-in-range -1.0 1.0))
            (square (random-in-range -1.0 1.0)))))
  (estimate-integral in-circle -1.0 1.0 -1.0 1.0 100000))

(define (square x)
  (* x x))

(display (estimate-pi)) (newline)
