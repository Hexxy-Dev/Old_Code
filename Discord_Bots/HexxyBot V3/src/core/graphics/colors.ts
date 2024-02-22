import { ColorResolvable } from 'discord.js';

type Colors = {
    Primary: ColorResolvable,
    Info: ColorResolvable,
    Error: ColorResolvable,
    Warn: ColorResolvable
}

const Colors : Colors = {
    Primary: '#000',
    Info: '#43b581',
    Error: '#faa619',
    Warn: '#f14846'
};
export default Colors;