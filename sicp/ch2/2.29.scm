(define (make-mobile left right)
  (list left right))

(define (make-branch length structure)
  (list length structure))

; a: left-branch, right-branch, branch-length and branch-structure selectors
(define (left-branch mobile)
  (car mobile))

(define (right-branch mobile)
  (car (cdr mobile)))

(define (branch-length branch)
  (car branch))

(define (branch-structure branch)
  (car (cdr branch)))

; b: total-weight procedure
(define (total-weight mobile)
  (cond ((null? mobile) 0)
        ((not (pair? mobile)) mobile)
        (else
          (+
            (total-weight (branch-structure (left-branch mobile)))
            (total-weight (branch-structure (right-branch mobile)))))))

; c: check if a mobile is balanced
(define (mobile-balanced? mobile)
  (cond ((not (pair? mobile)) #t)
        (else
          (let ((left (left-branch mobile))
                (right (right-branch mobile)))
            (let ((left-struct (branch-structure left))
                  (right-struct (branch-structure right)))
              (and
                (= (* (branch-length left) (total-weight left-struct))
                   (* (branch-length right) (total-weight right-struct)))
                (mobile-balanced? left-struct)
                (mobile-balanced? right-struct)))))))

; d: only the right-branch and the branch-structure selectors
;;   should be changed (that's the beauty of abstraction) changes below
(define (right-branch- mobile)
  (cdr mobile))

(define (branch-structure- branch)
  (cdr branch))

; Test code
(define m1 (make-mobile (make-branch 1 10) (make-branch 1 10)))
(define m2 (make-mobile (make-branch 1 m1) (make-branch 1 m1)))
(define m3 (make-mobile (make-branch 1 m2) (make-branch 1 m2)))

(display (total-weight m1)) (newline)
(display (total-weight m2)) (newline)
(display (total-weight m3)) (newline)
(display (mobile-balanced? m1)) (newline)
(display (mobile-balanced? m2)) (newline)
(display (mobile-balanced? m3)) (newline)

(define a (make-mobile (make-branch 2 3) (make-branch 2 3)))
(define b (make-mobile (make-branch 10 a) (make-branch 12 5)))
(define c (make-mobile (make-branch 1 b) (make-branch 1 22)))

(display (total-weight a)) (newline)
(display (total-weight b)) (newline)
(display (total-weight c)) (newline)
(display (mobile-balanced? a)) (newline)
(display (mobile-balanced? b)) (newline)
(display (mobile-balanced? c)) (newline)
