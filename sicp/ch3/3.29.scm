(include "simulator.scm")

(define (or-gate a1 a2 output)
  (let ((a (make-wire))
        (b (make-wire))
        (out (make-wire)))
    (inverter a1 a)
    (inverter a2 b)
    (and-gate a b out)
    (inverter out output)
    'ok))

(define a (make-wire))
(define b (make-wire))
(define out (make-wire))

; The delay time is two times inverter-delay plus one and-gate-delay
(probe 'out out)
(set-signal! a 1)
(set-signal! b 0)
(or-gate a b out)
(propagate)
(newline)
