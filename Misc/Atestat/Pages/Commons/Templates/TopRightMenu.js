function CreateTopRightMenu() {
    const html = `
    <div id="TopRightMenu">
        <input type="checkbox" id="TopRightMenuOpen">
        <div id="TopRightMenuHidden">
            <table>
                <tr>
                    <td><label for="DarkMode">DarkMode</label></td>
                    <td><input type="radio" name="ColorSchemeMenuOption" id="DarkMode" checked></td>
                </tr>
                <tr>
                    <td><label for="LightMode">LightMode</label></td>
                    <td><input type="radio" name="ColorSchemeMenuOption" id="LightMode"></td>
                </tr>
            </table>
            <a id="MenuBackButton" href="javascript:history.back(-1)">Back Home</a>
        </div>
    </div>
    `;
    return html;
}
document.body.innerHTML = CreateTopRightMenu() + document.body.innerHTML;