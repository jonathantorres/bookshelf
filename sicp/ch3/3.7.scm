(define (make-account balance password)
  (define joint-password '())
  (define (withdraw amount)
    (if (>= balance amount)
      (begin
        (set! balance (- balance amount))
        balance)
      "Insufficient Funds"))
  (define (deposit amount)
    (set! balance (+ balance amount))
    balance)
  (define (set-joint-password pass)
    (begin
      (set! joint-password pass)
      #t))
  (define (dispatch p m)
    (if (or (eq? p password) (eq? p joint-password))
      (cond ((eq? m 'withdraw) withdraw)
            ((eq? m 'deposit) deposit)
            ((eq? m 'set-joint-password) set-joint-password)
            (else
              (error "Unknown request -- MAKE-ACCOUNT" m)))
      (lambda (x) "Incorrect Password")))
  dispatch)

(define (make-joint account acc-pass new-acc-pass)
  (let ((joint-set (account acc-pass 'set-joint-password)))
    (if (joint-set new-acc-pass)
      account
      (lambda (x) "Incorrect Password"))))

(define peter-acc (make-account 100 'secret))
(define paul-acc (make-joint peter-acc 'secret 'foobar))

(display ((peter-acc 'secret 'withdraw) 25)) (newline) ; 75
(display ((paul-acc 'foobar 'withdraw) 25)) (newline) ; 50
(display ((peter-acc 'secret 'withdraw) 25)) (newline) ; 25

