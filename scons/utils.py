import os
import SCons
import SCons.Action

ActionFactory = SCons.Action.ActionFactory

def CreateSymlinkFunc(dest, src, isDirectory = True):
    dest = str(dest)
    src = str(src)
    SCons.Node.FS.invalidate_node_memos(dest)
    if not os.path.exists(dest):
        os.symlink(
            src=os.path.abspath(src),
            dst=os.path.abspath(dest),
            target_is_directory=isDirectory
        )

def CreateSymlinkStrFunc(dest, src):
    return "CreateSymlink(%s, %s)" % (src, dest)

CreateSymlink = ActionFactory(
    actfunc=CreateSymlinkFunc,
    strfunc=CreateSymlinkStrFunc
)

__all__ = [
    CreateSymlink
]