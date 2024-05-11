(include "simulator.scm")

(define (logical-or s1 s2)
  (cond ((= s1 1) 1)
        ((= s2 1) 1)
        (else
          0)))

(define (or-gate a1 a2 output)
  (define (or-action-procedure)
    (let ((new-value
            (logical-or (get-signal a1) (get-signal a2))))
      (after-delay or-gate-delay
                   (lambda ()
                     (set-signal! output new-value)))))
  (add-action! a1 or-action-procedure)
  (add-action! a2 or-action-procedure)
  'ok)

(define a (make-wire))
(define b (make-wire))
(define out (make-wire))

(probe 'out out)
(set-signal! a 1)
(set-signal! b 0)
(or-gate a b out)
(propagate)
(newline)
