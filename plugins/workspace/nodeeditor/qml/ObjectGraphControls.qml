import QtQuick 2.3

QtObject{

    objectName: "objectgraph"

    property Component objectNodeProperty: ObjectNodeMember{}

    function removeActiveItem(){
        var activeItem = lk.layers.workspace.panes.activeItem
        if ( activeItem.objectName === 'objectGraph' ){
            if ( activeItem.selectedEdge ){
                activeItem.removeEdge(activeItem.selectedEdge)
            }
        }
    }

    function nodeEditMode(){
        var panes = lk.layers.workspace.panes
        panes.reset()
        var fe = panes.createPane('editor', {}, [400, 0])

        var containerUsed = panes.container
        if ( containerUsed.orientation === Qt.Vertical ){
            for ( var i = 0; i < containerUsed.panes.length; ++i ){
                if ( containerUsed.panes[i].paneType === 'splitview' &&
                     containerUsed.panes[i].orientation === Qt.Horizontal )
                {
                    containerUsed = containerUsed.panes[i]
                    break
                }
            }
        }

        panes.splitPaneHorizontallyWith(containerUsed, 0, fe)
        fe.document = project.openTextFile(project.active.path)

        var editor = fe
        var codeHandler = editor.code.language
        var rootPosition = codeHandler.findRootPosition()

        var paletteFunctions = lk.layers.workspace.extensions.editqml.paletteFunctions

        paletteFunctions.shapeImports(editor)
        paletteFunctions.shapeRoot(editor, function(ef){
            var objectContainer = ef.visualParent
            var nodePalette = paletteFunctions.openPaletteInObjectContainer(objectContainer, 'NodePalette')
            nodePalette.child.resize(objectContainer.width - 50, editor.height - 170)
        })
    }
}
