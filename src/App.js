import './App.css';
import { Routes, Route, HashRouter } from 'react-router-dom';
// import Home from './Pages/Home'
import ViewDataBase from './Pages/ViewDataBase';
import NoPage from './Pages/NoPage';
import axios from 'axios';

axios.get('https://54.183.24.168:4000/listDBs')
  .then(response => {
    console.log(response.data);
  })
  .catch(error => {
    console.error(error);
  });

function App() {


  return (
    <div className="App">
      <HashRouter>
        <Routes>
          {/* <Route index element={<Home />} /> */}
          <Route index element={<ViewDataBase />}/>
          <Route path="/viewDataBase" element={<ViewDataBase />} />
          {/* <Route path="/viewDataBase" element={<ViewDataBase />} /> */}
          <Route path="*" element={<NoPage />} />
        </Routes>
      </HashRouter>

    </div>
  );
}

export default App;
