; Here are some somple examples of LISP functions. 
; No particular order, no particular anything, really.
; Typed them up as I thought of them, is all.

; I used "first" for "car" and "rest" for "cdr" in some places.

; Bill Mahoney
; CSCI 4220

; Here's a simple function - add one to each element in the list.
; Also we can demonstrate "cond".
(defun add1 (l)
  (cond ((null l) nil) ; Empty list returns empty list
	((numberp (first l)) ; Numbers return 1 + number 
	 (cons (+ 1 (first l)) (add1 (rest l))))
	((atom (first l)) ; Not a number? Just pass it through
	 (cons (first l) (add1 (rest l))))
	(t nil))) ; None of the above? Return nil

; Same as above, but much simpler to implement using mapcar
(defun plus1 (a) (+ 1 a))
(defun fancy-add1 (l)
  (mapcar 'plus1 l))

; Same as above, but even nicer, using a "lambda"; These are
; anonymous procedures. Assuming I spelled anonymous right...
(defun fancier-add1 (l)
  (mapcar '(lambda (a) (+ 1 a)) l))

; Here's some things that operate on "stacks"; let's assume a
; global stack called "stk"
(defun mypush (atom)
  (setq stk (cons atom stk))) ; Trivial.
(defun mypop () ; return the top, too...
  (let ((temp (car stk)))
    (setq stk (cdr stk))
    temp))

; Tree traversals are also pretty easy. Here's a binary search tree.
; The way this is done is (root (left-tree) (right-tree)). Can also
; use "NIL" instead of () for the leaves.
(setq my-bst (list 12
		   '(8 (4 () ()) (10 (9 () ()) ()))
		   '(30 () (50 (40 () ()) (80 () ())))
		   ))

; This will print them in prefix order; it has the slight
; down-side that it will also print "nil" at the end.
(defun preorder (tree)
  (cond ((null tree) nil)
	(t (print (car tree))
	   (preorder (cadr tree))
	   (preorder (caddr tree))
	   )))

; OK, so this will make a new list from the tree, in prefix order.
; Note that all this really does is remove the NILs from the tree.
(defun preorder-list (tree)
  (cond ((null tree) nil)
	(t (cons (cons (car tree)
		       (preorder-list (cadr tree)))
		 (preorder-list (caddr tree)))
	   )))

; Flatten a tree - that is, any sub-lists are elevated. 
; Example: (a (b c)) becomes (a b c).
(defun flatten (lst)
  ; (print (list 'here-we-are lst))
  (cond ((null lst) nil)
	((atom lst) 
	 (list lst))
	(t (append (flatten (car lst)) (flatten (cdr lst))))
	))

; Now we can "really" do preorder
(defun flat-preorder-list (tree)
  (flatten (preorder-list tree)))

