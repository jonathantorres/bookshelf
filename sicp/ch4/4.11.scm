(include "metacircular-evaluator.scm")

(define (make-frame var val)
  (cons 'frame (map cons var val)))

(define (add-binding-to-frame! var val frame)
  (set-cdr!
    frame
    (cons
      (cons var val)
      (cdr frame))))

(define (set-variable-to-frame! var val frame)
  (let ((find #f)) 
    (set-cdr! frame 
              (map (lambda (pair)
                     (if (eq? (car pair) var)
                       (begin
                         (set! find #t)
                         (cons var val))
                       pair))
                   (cdr frame)))
    find))

(define (set-variable-value! var val env)
  (define (env-loop env) 
    (if (eq? env the-empty-environment)
      (error "Unbound variable -- SET!" var)
      (if (set-variable-to-frame! (first-frame frame))
        'done
        (env-loop (enclosing-environment env)))))
  (env-loop env))

(define (define-variable! var val env)
  (let ((frame (first-frame env)))
    (if (set-variable-to-frame! var val frame)
      'done
      (add-binding-to-frame! var val frame))))

; sample program
(define prog '(* 1 2 3))

(user-print (eval prog the-global-environment)) (newline)
