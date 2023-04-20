import Header from '../Components/Header'

export default function CreateDataBase() {
    this.state = {fileUploadState:""}
    fileUploadButton = () => {
        document.getElementById('fileButton').click();
        document.getElementById('fileButton').onchange = () =>{      
        this.setState({
            fileUploadState:document.getElementById('fileButton').value
                });
            }
        }
    return (
        <>
            <Header />
            <h2> Create Database Page </h2>
            <div>
                <input id="fileButton" type="file" hidden />
                <button onClick={this.fileUploadButton}>
                    Image Upload
                </button>
                {this.state.fileUploadState}
                
                </div>
            
        </>
    )
}

