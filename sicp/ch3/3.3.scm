(define (make-account balance password)
  (define (withdraw amount)
    (if (>= balance amount)
      (begin
        (set! balance (- balance amount))
        balance)
      "Insufficient Funds"))
  (define (deposit amount)
    (set! balance (+ balance amount))
    balance)
  (define (dispatch p m)
    (if (eq? p password)
      (cond ((eq? m 'withdraw) withdraw)
            ((eq? m 'deposit deposit))
            (else
              (error "Unknown request -- MAKE-ACCOUNT" m)))
      (lambda (x) "Incorrect Password")))
  dispatch)

(define acc (make-account 100 'secret-password))

(display ((acc 'secret-password 'withdraw) 50)) (newline)
(display ((acc 'secret 'withdraw) 50)) (newline)
