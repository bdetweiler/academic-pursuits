; Lisp Family Tree
; Brian Detweiler
;
; Here is the family we want to use.

(setq family '(
                (Dora Ed
                    (Frank Gloria 
                        (Hannah)
                        (Ingrid James)
                        (Karen Lou 
                            (Matt) 
                            (Nathan)
                        )
                     )
                     (Olive)
                     (Patrick Quady 
                        (Renee)
                     )
                 )
               )
)


; Flatten a tree - that is, any sub-lists are elevated. 
; Example: (a (b c)) becomes (a b c).
(defun flatten(lst)
    (
        cond 
        (
            (null lst) 
                nil
        )
	    (
            (atom lst) 
	            (list lst)
        )
	    (
            t 
            (
                append
                    (flatten (car lst)) 
                    (flatten (cdr lst))
            )
        )
	)
)



(setq cousinslst ())

(defun cousins(name)
    (setq cousinslst ())
    (setq familylst (flatten family))
    (setq siblingslst (siblings name))

    (setq allcousins (g-children (car (g-parents name))))

    (
        loop for element in allcousins do 
        (
            cond
            (
                (null element) 
                    cousinslst
            )
            (
                (atom element) 
                    (
                        cond
                        (
                            ; If it's the person we queried for, don't include them in the list
                            (eq element name)
                                t
                        )   
                        (
                            t
                                (
                                    if (member element siblingslst)
                                    (
                                        setq cousinslst (cons nil cousinslst)
                                    )
                                    (
                                        setq cousinslst (cons element cousinslst)
                                    )
                                )
                        )
                    )
            )
            (
                t
                    cousinslst
            )
        )
    )

    (flatten cousinslst)
)



(setq siblingslst ())

(defun siblings(name)
    (setq siblingslst ())
    (setq familylst (flatten family))

    (setq allsiblings (children (car (parents name))))
    ;(setq g-childlst (g-children name))

    (
        loop for element in allsiblings do 
        (
            cond
            (
                (null element) 
                    siblingslst
            )
            (
                (atom element) 
                    (
                        cond
                        (
                            ; If it's the person we queried for, don't include them in the list
                            (eq element name)
                                t
                        )   
                        (
                            t
                                (setq siblingslst (cons element siblingslst))
                        )
                    )
            )
            (
                t
                    siblingslst
            )
        )
    )

    (flatten siblingslst)
)




(setq g-g-parentslst ())

(defun g-g-parents(name)
    (setq g-g-parentslst ())
    (setq familylst (flatten family))

    ;(setq g-childlst (g-children name))

    (
        loop for element in familylst do 
        (
            cond
            (
                (null element) 
                    g-g-parentslst
            )
            (
                (atom element) 
                    (
                        cond
                        (
                            (member name (g-g-children element))
                                (setq g-g-parentslst (cons element g-g-parentslst))
                                g-g-parentslst
                        )
                        (
                            t
                                g-g-parentslst
                        )
                    )
            )
            (
                t
                    g-g-parentslst
            )
        )
    )

    (flatten g-g-parentslst)
)







(setq g-parentslst ())

(defun g-parents(name)
    (setq g-parentslst ())
    (setq familylst (flatten family))

    ;(setq g-childlst (g-children name))

    (
        loop for element in familylst do 
        (
            cond
            (
                (null element) 
                    g-parentslst
            )
            (
                (atom element) 
                    (
                        cond
                        (
                            (member name (g-children element))
                                (setq g-parentslst (cons element g-parentslst))
                                g-parentslst
                        )
                        (
                            t
                                g-parentslst
                        )
                    )
            )
            (
                t
                    g-parentslst
            )
        )
    )

    (flatten g-parentslst)
)



(setq parentslst ())

(defun parents(name)
    (setq parentslst ())
    (setq familylst (flatten family))

    ;(setq g-childlst (g-children name))

    (
        loop for element in familylst do 
        (
            cond
            (
                (null element) 
                    parentslst
            )
            (
                (atom element) 
                    (
                        cond
                        (
                            (member name (children element))
                                (setq parentslst (cons element parentslst))
                                parentslst
                        )
                        (
                            t
                                parentslst
                        )
                    )
            )
            (
                t
                    parentslst
            )
        )
    )

    (flatten parentslst)
)



(setq g-g-childlst())

(defun g-g-children(name)
    (setq g-g-childlst ())
    (setq g-childlst (g-children name))

    (
        loop for element in g-childlst do 
        (
            cond
            (
                (null element) 
                    g-g-childlst
            )
            (
                (atom element) 
                    (setq g-g-childlst (cons (children element) g-g-childlst))
                    g-g-childlst
            )
            (
                t
                    g-g-childlst
            )
        )
    )

    (flatten g-g-childlst)
)


(setq g-childlst())

(defun g-children(name)
    (setq g-childlst ())
    (setq childlst (children name))

    (
        loop for element in childlst do 
        (
            cond
            (
                (null element) 
                    g-childlst
            )
            (
                (atom element) 
                    (setq g-childlst (cons (children element) g-childlst))
                    g-childlst
            )
            (
                t
                    g-childlst
            )
        )
    )

    (flatten g-childlst)
)


(setq mychildren ())
(setq childlst ())


(defun children(name)
    (setq childlst())
    (
        cond 
        (
            (null name) 
                nil
        )
        (   
            (atom name)
                (child-helper name family)
                childlst
        )
        (
            t
                nil
        )
    )
)

(defun child-helper(name lst)
    (
        cond 
        (
            (null lst) 
                nil
        )
        (  
            (atom lst) 
                lst
        )
        (
            t 
            (
                cond 
                (
                    (eq name (child-helper name (car lst)))
                        (
                            cond
                            (
                                (atom (car (cdr lst)))
                                    (setq tmp (discard-spouse (cdr lst)))
                                    (setq mychildren (extract-children tmp))
                            )
                            (
                                ; The second elment is a sub-list, we just pass the whole list
                                t
                                    (setq tmp (discard-spouse lst))
                                    (setq mychildren (extract-children tmp))
                            )
                        )
                )
                (
                    t
                        (child-helper name (cdr lst))
                )
            )
        )
    )
)

; We're at the right level. Everything in here is children.
; But there are also grandchildren, and great-grandchildren.
; We just want the 0th element of each sub-list
(defun extract-children(lst)
    (
        cond 
        (
            (null lst) 
                nil
        )
        (
            (atom lst) 
                lst
        )
        (
            t 
            (
                loop for element in lst do 
                (
                    cond
                    (
                        (null element) 
                            nil
                    )
                    (
                        (atom element) 
                            element
                    )
                    (
                        t
                            (setq childlst (cons (car element) childlst))
                    )
                )
            )
         )
    )
)


; When calling this function, we should have just the spouse, 
; and the children (and grand children, etc). So we want to 
; get rid of the spouse and just return the descendents.
(defun discard-spouse(lst)
    (
        cond 
        (
            (null lst) 
                nil
        )
        (
            ; This is the spouse
            ; Return everything after the spouse
            (atom (car lst))
                (cdr lst)
        )
        (
            ; Still looking for the spouse
            ; Remove a level of lists, and try again
            t 
            (
                discard-spouse (car lst)
            )
        )
    )
)
