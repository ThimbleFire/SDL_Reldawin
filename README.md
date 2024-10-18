Todo

Each UIElement should have its own list of children
this way buttons can be independently responsible for
declaring their own UIResizeableTexture.

We'll need to think about how that might impact the event system though.

So

    Create a UIWindow
    Add a body
        Add a header
            Add a label (title)
            Add a close button
        Add <?>
        Add a footer
            add a resize region