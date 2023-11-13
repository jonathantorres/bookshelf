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
  (let ((left-struct (branch-structure (left-branch mobile)))
        (right-struct (branch-structure (right-branch mobile))))
    (cond ((and (not (pair? left-struct)) (not (pair? right-struct)))
           (+ left-struct right-struct))
           ((not (pair? left-struct)) (+ left-struct (total-weight right-struct)))
           ((not (pair? right-struct)) (+ (total-weight left-struct) right-struct))
           (else
             (+ (total-weight left-struct) (total-weight right-struct))))))

; c: check if a mobile is balanced
(define (mobile-length mobile)
  (let ((left (left-branch mobile))
        (right (right-branch mobile)))
    (let ((left-subtree-length
            (if (pair? (branch-structure left))
              (mobile-length (branch-structure left)) 0))
          (right-subtree-length
            (if (pair? (branch-structure right))
              (mobile-length (branch-structure right)) 0)))
      (+
        (branch-length left)
        (branch-length right)
        left-subtree-length
        right-subtree-length))))

(define (mobile-balanced? mobile)
  (let ((left (left-branch mobile))
        (right (right-branch mobile)))
    (let ((left-struct (branch-structure left))
          (right-struct (branch-structure right)))
      (cond ((and (pair? left-struct) (pair? right-struct))
               (and (mobile-balanced? left-struct) (mobile-balanced? right-struct)))
            ((pair? left-struct)
             (= (* (mobile-length left-struct) (total-weight left-struct))
                (* (branch-length right) right-struct)))
            ((pair? right-struct)
             (= (* (branch-length left) left-struct)
                (* (mobile-length right-struct) (total-weight right-struct))))
            (else
              (= (* (branch-length left) left-struct)
                 (* (branch-length right) right-struct)))))))

; d: only the right-branch and the branch-structure selectors
;;   should be changed (that's the beauty of abstraction) changes below
(define (right-branch- mobile)
  (cdr mobile))

(define (branch-structure- branch)
  (cdr branch))

; Test code
(define m1 (make-mobile (make-branch 1 15) (make-branch 1 15)))
(define m2 (make-mobile (make-branch 1 m1) (make-branch 1 m1)))
(define m3 (make-mobile (make-branch 1 m2) (make-branch 1 m2)))

(display (total-weight m1)) (newline)
(display (total-weight m2)) (newline)
(display (total-weight m3)) (newline)
(display (mobile-length m3)) (newline)
(display (mobile-balanced? m1)) (newline)
(display (mobile-balanced? m2)) (newline)
(display (mobile-balanced? m3)) (newline)

(define a (make-mobile (make-branch 2 3) (make-branch 2 3)))
(display (total-weight a)) (newline)
(define d (make-mobile (make-branch 10 a) (make-branch 12 5)))

 ; this should be true
(display (mobile-balanced? d)) (newline)
