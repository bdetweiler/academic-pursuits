; Here are some small examples of functions.
; Bill Mahoney - February 21, 2006

; my-rev reverses a list, similar to "reverse"
(defun my-rev ( L )
  ; (print L)
  (cond  ((null L) nil)
	 ((atom L) L)
	 (T (append (my-rev (rest L)) (list (car L))))
	 ))


; count-atoms will examione a list and count up the elements.
; It goes down into sub-lists as well.
(defun count-atoms ( L )
  (print L) ; Just for show. Wound not be in a "real" function.
  (cond  ((null L) 0)
	 ((atom L) 1)
	 ; The only other thing it can be is a list. But is the first
	 ; element a list itself? (Or, do we really need this and can't
	 ; we just add count of car + count of cdr? Oh well.
	 ((listp (car L)) 
	  (+ (count-atoms (car L)) (count-atoms (cdr L))))
	 ; Then it must be a list, with the first item an atom.
	 (T (+ 1 (count-atoms (cdr L))))
	 ))


; same-thing is a function like "equal". But we already have "equals"!
; Well, it's worth looking at...
(defun same-ones (L1 L2)
  (format t "Checking: ") (prin1 L1) (format t " == ") (print L2)
  ; eq, remember, compares pointers. So we can use it to test atoms.
  (cond ( (and (null L1) (null L2)) T ) ; Empty lists are equal.
	( (and (atom (car L1)) (atom (car L2)) (eq (car L1) (car L2)))
	  (same-ones (cdr L1) (cdr L2)))
	( (and (listp (car L1)) (listp (car L2)) (same-ones (car L1) (car L2)))
	  (same-ones (cdr L1) (cdr L2)))
	( T nil ) ; if you get here they must NOT be equal.
	))

; Let's look up some things in a rule database. The rules will be as follows:
(setq rules '((auto has (wheels axles doors roof))
	      (bus has (wheels axles doors roof windows))
	      (bicycle has (wheels axles pedals spokes shifters))
	      (tank has (wheels tread turret shells))))

; Now this allows us to ask questions. Which things have wheels? That sort of thing.
; The return value is a bit unexpected. This is set up so that we return T if ANY 
; rule matched. That's fine, because we want to recurse and print all of them that
; match, But it makes it "not make sense" if you want to co-join things, as in:
;         (and (it-has 'spokes) (it-has 'tread)) 
; because none of these objects have BOTH spokes and tread. 
(defun it-has ( feature )
  (examine feature rules))
(defun examine ( feature rulelist )
  (let ((rule (car rulelist))) ; Need the double paren's on that one...
    ; (format t "Looking for feature ") (prin1 feature) (format t " In ") (print rule)
    (cond ( (null rule) nil)
	  ( (member feature (caddr rule))
	    (prin1 (car rule)) (format t " has ") (print feature)
	    (examine feature (cdr rulelist))
	    T)
	  ( T (examine feature (cdr rulelist)))
	  )))

; Let's pretend that (flat) lists are sets. For example, (A B C) is a set and (A F G) is
; a set. Let's determine the intersection of the two sets and return it as a list/set.
(defun intersect (A B)
  ; (print a) (print b)
  (cond ( (or (null A) (null b)) nil) ; intersection of an empty set is empty.
	( (member (car a) b) ; First element in A --IS-- in B, so...
	  (cons (car a) (intersect (cdr a) b)))
	( T (intersect (cdr a) b))
	) )
